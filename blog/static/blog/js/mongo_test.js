var MongoClient = require('mongodb').MongoClient;
var assert = require('assert');
var ObjectId = require('mongodb').ObjectID;

var url='mongodb://localhost:27017/test';

var insertDocument=function(db,callback){
	db.collection('restaurants').insertOne({
		address:{
			street: "2 Avenue",
			zipcode: 10075,
			building: 1480,
			coord: [-73.96, 40.77] 
		},
		borough: 'Manhattan',
		cuisine: 'Italian',
		grade: [
		{
			date: new Date('2014-10-01T00:00:00Z'),
			grade: 'A',
			score: 11
		},
		{
			date: new Date('2014-01-16T00:00:00Z'),
			grade: 'B',
			score: 17
		}
		],
		name: 'Vella',
		restaurant_id: '41704620'
	},function(err, result){
		assert.equal(err,null);
		console.log('Insert complete!');
		callback();
	});

};

var findRestaurants=function(db,callback){
	var cursor=db.collection('restaurants').find({'address.zipcode': '10016',cuisine: 'Other'});
	cursor.each(function(err,doc){
		assert.equal(err,null);
		if(doc!=null){
			console.dir(doc);
		}else{
			callback();
		}
	});
};

var updateRestaurants=function(db,callback){
	db.collection('restaurants').updateMany(
			{'address.zipcode':'10016'},
			{
				$currentDate: {'lastModified': true}
			}, function(err, results){
				console.log(results);
				callback();
			});
}
var aggregateRestaurants = function(db, callback) {
   db.collection('restaurants').aggregate(
     [
       { $group: { "_id": "$borough", "mycount": { $sum: 1 } } }
     ]).toArray(function(err, result) {
     assert.equal(err, null);
     console.log(result);
     callback(result);
   });
};

MongoClient.connect(url,function(err,db){
	assert.equal(null,err);
	aggregateRestaurants(db,function(){
		db.close();
	});
});
