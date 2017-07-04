from django.conf import settings
from django.conf.urls import url
from django.conf.urls.static import static 

from . import views

urlpatterns = [
        url(r'^(?P<imgname>image/[^/]+)$', views.getImage,name='imgname'),
        url(r'^(?P<codefile>code/.+)$', views.getCode,name='codefile'),
        url(r'^(?P<filename>[^/]+)/$', views.article, name='article'),
        url(r'^comment/get/([^/]+)/$', views.getComment, name='get comment'),
        url(r'^meta/([^/]+)/$', views.getMeta, name='meta'),
        url(r'^comment/add$',views.addComment),
        url(r'^get/all/articles$',views.getAllArticles),
        url(r'^$',views.home),
]

