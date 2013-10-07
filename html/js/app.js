'use strict';

// Declare app level module which depends on filters, and services

var myApp = angular.module('myApp', ['myApp.filters', 'myApp.services', 'myApp.directives']);

myApp.config(['$routeProvider', function($routeProvider) {
    $routeProvider.
	when('/home', {templateUrl: 'partials/home.html', controller: homeController}).
	when('/about', {templateUrl: 'partials/about.html', controller: homeController}).
	when('/projects', {templateUrl: 'partials/projects.html', controller: homeController}).
	when('/blog', {templateUrl: 'blog.chrisostrouchov.html'}).
	otherwise({redirectTo: '/home'});
}]);

myApp.run(function($rootScope, $location, $anchorScroll, $routeParams) {
    $rootScope.$on('$routeChangeSuccess', function(newRoute, oldRoute) {
	$location.hash($routeParams.scrollTo);
	$anchorScroll();
     });
});