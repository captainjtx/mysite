var app = angular.module('commentBox', []);
app.config(function($httpProvider) {
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
});
app.controller('FrmController', [
		'$scope',
		'$http',
		function($scope,$http) {
			$scope.commonStaticURL='../../';
			$scope.comment = [];
			$scope.btn_add = function() {
				if($scope.txtComment !=''){
					//$scope.comment.push($scope.txtComment);
					$http({
						method: 'POST',
						url: '/blog/comment/add',
						data: { name: $scope.txtName ,
						       	email: $scope.txtEmail,
						       	comment: $scope.txtComment,
							article: $('.blog-post-title').text() 
					       	}
					}).then(function successCallback(response) {
						// this callback will be called asynchronously
						// when the response is available
						console.log(response);
					}, function errorCallback(response) {
						// called asynchronously if an error occurs
						// or server returns response with an error status.
						console.log(response);
						console.log('fail');
					});
				}
			}
			$scope.remItem = function($index) {
				$scope.comment.splice($index, 1);
			}
		}]);
