from django.shortcuts import render
from django.http import HttpResponse

def sort(request):
    return render(request,'blog/sort.html')

def dataStructure(request):
    return render(request,'blog/data-structure.html')

# Create your views here.
