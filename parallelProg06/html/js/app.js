'use strict';

// Declare app level module which depends on filters, and services
angular.module('myApp', ['myApp.filters', 'myApp.services', 'myApp.directives', 'ui.ace']).
    config(['$routeProvider', function($routeProvider) {
	$routeProvider.
	    when('/home', {templateUrl: 'partials/home.html', controller: homeController}).
	    when('/about', {templateUrl: 'partials/about.html', controller: homeController}).
	    when('/projects', {templateUrl: 'partials/projects.html', controller: homeController}).
	    when('/blog', {templateUrl: 'blog.chrisostrouchov.html'}).
	    otherwise({redirectTo: '/home'});
    }]);