from django.http import HttpResponse
from django.http import Http404
from django.contrib.staticfiles.templatetags.staticfiles import static
from mysite import settings
from django.contrib.staticfiles.storage import staticfiles_storage
import os.path
def getImage(request,imgname):
    extension=os.path.splitext(imgname)[1]
    if extension=='.svg':
        ct="image/svg+xml"
    elif extension=='.png':
        ct="image/png"
    try:
        f=staticfiles_storage.open(imgname);
        return HttpResponse(f.read(), content_type=ct)
    except IOError:
        raise Http404(static(imgname)+' does not exist')
