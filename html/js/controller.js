'use strict';

/* Controllers */

var sidebarController = function($scope, $location, $anchorScroll) {
    $scope.scrollTo = function(id) {
	var old = $location.hash();
	$location.hash(id);
	$anchorScroll();

	$location.hash(old);
    }
};

var navigationController = function($scope, $location) {
    $scope.location = $location;
};

var homeController = function () {
  
};

