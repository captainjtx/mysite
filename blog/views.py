from django.shortcuts import render
from django.http import HttpResponse
from blog.models import Comment ,Visitor, Article
import datetime 
import json 
from django.core.serializers.json import DjangoJSONEncoder
from django.http import Http404
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
        
def getComment(request,title):
    dict={}
    dict['success']=0
    info='Comment fetch success'
    dict['title']=title
    try:
        articleID=Article.objects.get(title=title)
    except Article.DoesNotExist:
        raise Http404('Article "'+ title+'.html" does not exist')

    comments=Comment.objects.filter(article=articleID)
    data=[]
    for ite in comments:
        visitorName=Visitor.objects.get(pk=ite.visitor_id).name
        content=ite.content
        vote=ite.vote
        pub_date=ite.pub_date
        data+=[{'visitor': visitorName, 'content': content, 'vote': vote, 'datetime': pub_date.isoformat()}]

    dict['comment']=data;
    dict['success']=1
    dict['message']=info;

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
    return render(request,'blog/home.html')
# Create your views here.
