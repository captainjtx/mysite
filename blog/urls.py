from django.conf import settings
from django.conf.urls import url
from django.conf.urls.static import static 

from . import views

urlpatterns = [
        url(r'^$',views.home),
        url(r'^home/$',views.home),
        url(r'^about/$',views.about),
        url(r'^(?P<filename>[^/]+)/$', views.article, name='article'),
        url(r'^comment/get/([^/]+)/$', views.getComment, name='get comment'),
        url(r'^comment/add$',views.addComment),
]

