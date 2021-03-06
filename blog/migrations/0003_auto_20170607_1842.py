# -*- coding: utf-8 -*-
# Generated by Django 1.11 on 2017-06-07 18:42
from __future__ import unicode_literals

import datetime
from django.db import migrations, models
from django.utils.timezone import utc


class Migration(migrations.Migration):

    dependencies = [
        ('blog', '0002_auto_20170605_0328'),
    ]

    operations = [
        migrations.AddField(
            model_name='article',
            name='excerpt',
            field=models.TextField(max_length=1000, null=True),
        ),
        migrations.AlterField(
            model_name='comment',
            name='pub_date',
            field=models.DateTimeField(default=datetime.datetime(2017, 6, 7, 18, 42, 23, 757655, tzinfo=utc), verbose_name='Comment date'),
        ),
    ]
