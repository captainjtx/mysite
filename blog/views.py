from django.shortcuts import render
from django.http import HttpResponse
from blog.models import Comment ,Visitor, Article
import datetime 
import json 
from django.core.serializers.json import DjangoJSONEncoder
from django.http import Http404
from django.contrib.staticfiles.templatetags.staticfiles import static
from mysite import settings
import os.path
from django.contrib.staticfiles.storage import staticfiles_storage

def getAllArticles(request):
    dict={}
    dict['success']=0
    try:
        allArticles=Article.objects.all()
    except Article.DoesNotExist:
        raise Http404('No article records !')
    data=[]
    for art in allArticles:
        data+=[{'title': art.title,'datetime': art.pub_date.isoformat(),'file': art.file,'excerpt': art.excerpt}]

    dict['success']=1
    dict['articles']=data;
    obj=json.dumps(dict,cls=DjangoJSONEncoder)
    return HttpResponse(obj)

def getMeta(request,filename):
    dict={}
    dict['filename']=filename;
    try:
        articleID=Article.objects.get(file=filename)
    except Article.DoesNotExist:
        raise Http404('Article "'+ filename +'" does not exist')
    dict['title']=articleID.title;
    dict['pub_date']=articleID.pub_date;
    dict['modified_date']=articleID.modified_date;
    obj=json.dumps(dict,cls=DjangoJSONEncoder)
    return HttpResponse(obj)

def getComment(request,filename):
    dict={}
    dict['success']=0
    info='Comment fetch success'
    dict['filename']=filename
    try:
        articleID=Article.objects.get(file=filename)
    except Article.DoesNotExist:
        raise Http404('Article "'+ filename +'" does not exist')

    comments=Comment.objects.filter(article=articleID)
    data=[]
    for ite in comments:
        visitorName=Visitor.objects.get(pk=ite.visitor_id).name
        content=ite.content
        vote=ite.vote
        pub_date=ite.pub_date
        data+=[{'visitor': visitorName, 'content': content, 'vote': vote, 'datetime': pub_date.isoformat()}]

    dict['comment']=data
    dict['success']=1
    dict['message']=info

    obj=json.dumps(dict,cls=DjangoJSONEncoder)
    return HttpResponse(obj)

def addComment(request):
    dict = {}
    info = 'Comment upload success'
    dict['success']=0;
    try:
        if request.method=='POST':
            req=json.loads(request.body)

            name = req["name"]
            email = req["email"]
            article= req['article'] 
            pub_date = datetime.datetime.now() 
            comment= req['comment']
            vote = -1;# not implemented yet

            dict['name']= name
            dict['email']=email
            dict['time']=pub_date.strftime('%c')
            dict['comment']=comment
            dict['article']=article

            if not Visitor.objects.filter(email=email).exists():
                newVisitor=Visitor(name=name,email=email)
                newVisitor.save()
            else:
                info='Email already exists !'

            articleID=Article.objects.get(title=article)
            visitorID=Visitor.objects.get(email=email)

            newComment=Comment(article=articleID,
                    visitor=visitorID,
                    content=comment,
                    vote=vote,
                    pub_date=pub_date)
            newComment.save()

            dict['success']=1;
    except:
        import sys
        info = "%s || %s" % (sys.exc_info()[0], sys.exc_info()[1])

    dict['message']=info
    obj=json.dumps(dict)
    return HttpResponse(obj)

def article(request,filename):
    try:
        articleID=Article.objects.get(file=filename)
    except Article.DoesNotExist:
        raise Http404('Article "'+ filename+'.html" does not exist')
    commentNum=Comment.objects.filter(article=articleID).count()
    context={'commentNum':commentNum}
    return render(request,'blog/'+filename+'.html',context)

def home(request):
    return render(request,'blog/home.html')

def about(request):
    return render(request,'blog/about.html')
# Create your views here.
def getImage(request,imgname):
    extension=os.path.splitext(imgname)[1]
    if extension=='.svg':
        ct="image/svg+xml"
    elif extension=='.png':
        ct="image/png"

    try:
        #try remote
        f=staticfiles_storage.open('blog/'+imgname)
        return HttpResponse(f.read(), content_type=ct)
    except IOError:
        #try to serve from local
        try: 
            with open('blog/static/blog/'+imgname, "rb") as f:
                return HttpResponse(f.read(), content_type=ct)
        except IOError:
                raise Http404('Image "'+ imgname+'" does not exist')
def getCode(request,codefile):
    try:
        f=staticfiles_storage.open('blog/'+codefile)
        content=f.read();
        return HttpResponse(content,content_type='text/plain')
    except IOError:
        raise Http404('Code file "'+ codefile +'" does not exist')
def getCV(request):
    try:
        f=staticfiles_storage.open('cv/cv.pdf');
        content=f.read();
        return HttpResponse(content,content_type='application/pdf')
    except IOError:
        try:
            for url in settings.STATICFILES_DIRS:
                try:
                    with open(url+'/cv/cv.pdf') as f:
                        return HttpResponse(f.read(), content_type='application/pdf')
                except IOError:
                    continue
        except IOError:
            raise Http404('"cv.pdf" does not exist')

def getBib(request):
    try:
        f=staticfiles_storage.open('bib/mypub.bib');
        content=f.read();
        return HttpResponse(content,content_type='text/plain')
    except IOError:
        try:
            for url in settings.STATICFILES_DIRS:
                try:
                    with open(url+'/bib/mypub.bib') as f:
                        return HttpResponse(f.read(), content_type='text/plain')
                except IOError:
                    continue
        except IOError:
            raise Http404('"mypub.tex" does not exist')
