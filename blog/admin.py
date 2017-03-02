from django.contrib import admin
from .models import Article,Comment,Reader,Tag

class ArticleAdmin(admin.ModelAdmin):
    list_display = ('title', 'pub_date')
    search_fields = ('title', )
    list_filter=('pub_date',)
    date_hierarchy = 'pub_date'
    ordering = ('-pub_date',)
    fields = ('title', 'pub_date', 'file')
class ReaderAdmin(admin.ModelAdmin):
    list_display = ('name', 'email')
    search_fields = ('name',)
    fields = ('name', 'email',)
class CommentAdmin(admin.ModelAdmin):
    list_display = ('article', 'reader','pub_date')
    list_filter=('pub_date',)
    date_hierarchy = 'pub_date'
    ordering = ('-pub_date',)
    fields = ('reader', 'article','content','vote','pub_date')
    raw_id_fields = ('reader',)

class TagAdmin(admin.ModelAdmin):
    filter_horizontal = ('article',)

admin.site.register(Article,ArticleAdmin)
admin.site.register(Comment,CommentAdmin)
admin.site.register(Reader,ReaderAdmin)
admin.site.register(Tag,TagAdmin)

# Register your models here.
