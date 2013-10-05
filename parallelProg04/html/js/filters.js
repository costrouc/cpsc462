'use strict';

/* Filters */

var myAppFilters = angular.module('myApp.filters', []);

myAppFilters.filter('interpolate', ['version', function(version) {
    return function(text) {
	return String(text).replace(/\%VERSION\%/mg, version);
    }
}]);