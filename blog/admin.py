from django.contrib import admin
from .models import Article,Comment,Visitor,Tag


admin.site.register(Article)
admin.site.register(Comment)
admin.site.register(Visitor)
admin.site.register(Tag)

# Register your models here.
