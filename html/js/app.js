'use strict';

var myApp = angular.module('myApp', ['myApp.filters', 'myApp.services', 'myApp.directives']);

myApp.config(['$routeProvider', function($routeProvider) {
    $routeProvider.
	when('/home', {templateUrl: 'partials/home.html', controller: homeController}).
	when('/about', {templateUrl: 'partials/about.html', controller: homeController}).
	when('/projects', {templateUrl: 'partials/projects.html', controller: homeController}).
	when('/blog', {templateUrl: 'partials/blog.html', controller: homeController}).
	otherwise({redirectTo: '/home'});
}]);

// My understanding of this feature is limited
myApp.run(function($rootScope, $location, $anchorScroll, $routeParams) {
    $rootScope.$on('$routeChangeSuccess', function(newRoute, oldRoute) {
	$location.hash($routeParams.scrollTo);
	$anchorScroll();
     });
});

