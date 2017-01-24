var app = angular.module('commentBox', []);
app.controller('FrmController', function($scope) {
	$scope.comment = [];
	$scope.btn_add = function() {
		if($scope.txtComment !=''){
			$scope.comment.push($scope.txtComment);
		}
	}
	$scope.remItem = function($index) {
		$scope.comment.splice($index, 1);
	}
});
