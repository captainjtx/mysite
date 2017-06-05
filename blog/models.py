from __future__ import unicode_literals

from django.db import models
from django.utils.timezone import now

class Article(models.Model):
    title=models.CharField(max_length=200,primary_key=True)
    pub_date=models.DateTimeField('Publish date')
    file=models.CharField(max_length=20,unique=True,null=True)
    def __str__(self):
        return self.title
    class Meta:
        ordering=['pub_date']

class Tag(models.Model):
    name=models.CharField(max_length=20,primary_key=True)
    article=models.ManyToManyField(Article)
    def __str__(self):
        return self.name
    class Meta:
        ordering=['name']

class Visitor(models.Model):
    email=models.EmailField(unique=True,verbose_name ='e-mail',primary_key=True)
    name=models.CharField(max_length=200)
    def __str__(self):
        return self.name
    class Meta:
        ordering=['name']
    
class Comment(models.Model):
    article=models.ForeignKey(Article)
    visitor=models.ForeignKey(Visitor,null=True)
    content=models.TextField('Comment content')
    vote=models.PositiveSmallIntegerField(default=0,blank=True)
    pub_date=models.DateTimeField('Comment date',default=now())
    def __str__(self):
        return self.visitor.name+' on '+ '"'+self.article.title+'"'
    class Meta:
        ordering=['article']



# Create your models here.
