'use strict';

/* Directives */

var myAppDirectives = angular.module('myApp.directives', []);

myAppDirectives.directive('appVersion', ['version', function(version) {
    return function(scope, elm, attrs) {
	elm.text(version);
    };
}]);

myAppDirectives.directive('editorText', function(fileText) {
    return function(scope, elm, attrs) {

	var acee = window.ace.edit(elm[0]);
	var session = acee.getSession();
	var renderer = acee.renderer;
	
	acee.setReadOnly(true);
	acee.setTheme("ace/theme/twilight");
	
	session.setUndoManager(new ace.UndoManager());
	session.setMode("ace/mode/c_cpp");
	session.setUseWrapMode(true);

	renderer.setShowGutter(true);
    	
	fileText.async(attrs.editorText).then(function(text) {
	    session.setValue(text);
	});
    };
});

