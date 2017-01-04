import QtQuick 2.0
import QtWebView 1.1

WebView {
    id: webView
    anchors.fill: parent
    url: "https://dev.portal.vip-consult.co.uk/"
    onLoadingChanged: runJavaScript("document.cookie.split(';')",
                                    function(cookieArray) {

                                        console.debug(cookieArray);

                                        for(var i=0;i < cookieArray.length;i++) {
                                            if(cookieArray[i].split('=')[0].trim()=='PHPSESSID'){

                                                console.log("setting cookies:"+cookieArray[i].split('=')[1]);

                                                root.cookie = cookieArray[i].split('=')[1];
                                                return;
                                            }

                                        }
                                    })
}
