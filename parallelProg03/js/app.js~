'use strict';

// Declare app level module which depends on filters, and services
angular.module('myApp', ['myApp.filters', 'myApp.services', 'myApp.directives']).
    config(['$routeProvider', function($routeProvider) {
	$routeProvider.
	    when('/home', {templateUrl: 'partials/home.html', controller: homeCtrl}).
	    when('/about', {templateUrl: 'partials/about.html', controller: homeCtrl}).
	    when('/projects', {templateUrl: 'partials/projects.html', controller: homeCtrl}).
	    when('/blog', {templateUrl: 'blog.chrisostrouchov.html'}).
	    otherwise({redirectTo: '/home'});
    }]);