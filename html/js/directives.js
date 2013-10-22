'use strict';

/* Directives */

var myAppDirectives = angular.module('myApp.directives', []);

myAppDirectives.directive('appVersion', ['version', function(version) {
    return function(scope, elm, attrs) {
	elm.text(version);
    };
}]);

myAppDirectives.directive('aceeditor', function(fileText) {
    return function(scope, element, attrs) {

	var acee = window.ace.edit(element[0]);
	var session = acee.getSession();
	var renderer = acee.renderer;
	
	acee.setReadOnly(true);
	acee.setTheme("ace/theme/twilight");
	
	session.setUndoManager(new ace.UndoManager());
	session.setMode("ace/mode/c_cpp");
	session.setUseWrapMode(true);

	renderer.setShowGutter(true);
    	
	fileText.async(attrs.src).then(function(text) {
	    session.setValue(text);
	});
    };
});

myAppDirectives.directive('markdownjax', function (fileText) {
    var converter = new Markdown.Converter();
    return {
	restrict: "A",
	link: function (scope, element, attrs) {
	    fileText.async(attrs.src).then(function(text) {
		var htmlText = converter.makeHtml(text);
		element.html(htmlText);
		MathJax.Hub.Typeset(element[0]);
	    });
        }
    }
});


