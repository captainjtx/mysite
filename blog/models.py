from __future__ import unicode_literals

from django.db import models

class Article(models.Model):
    title=models.CharField(max_length=200)
    content=models.TextField('Blog content')
    pub_date=models.DateTimeField('Date')




# Create your models here.
