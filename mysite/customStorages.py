from django.conf import settings
from storages.backends.s3boto import S3BotoStorage

class StaticStorage(S3BotoStorage):
    """uploads to S3 bucket, serves from cloudfront"""
    def __init__(self, *args, **kwargs):
        kwargs['custom_domain']=settings.AWS_CLOUDFRONT_DOMAIN
        super(StaticStorage, self).__init__(*args, **kwargs)
