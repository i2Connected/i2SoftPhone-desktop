import QtQuick.Dialogs 1.2 as Dialogs


import UtilsCpp 1.0

Dialogs.FileDialog {
	id:mainItem
	
	function getFileUrls(){
		var decodedFiles = [];
		for(var i = 0 ; i < fileDialog.fileUrls.length ; ++i)
			decodedFiles.push(UtilsCpp.decodePercentFromUtf8(fileDialog.fileUrls[i])) 
		return decodedFiles;
	}
	
	function getFileUrl(){
		return UtilsCpp.decodePercentFromUtf8(fileUrl)
	}
}