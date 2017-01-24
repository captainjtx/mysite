from django.conf import settings
from django.conf.urls import url
from django.conf.urls.static import static 

from . import views

urlpatterns = [
    url(r'^sort$', views.sort, name='sort'),
    url(r'^data-structure$', views.dataStructure, name='data-structure'),
]

