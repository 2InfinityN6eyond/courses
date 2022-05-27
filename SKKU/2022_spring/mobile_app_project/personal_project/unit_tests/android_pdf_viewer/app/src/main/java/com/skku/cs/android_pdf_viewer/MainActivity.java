package com.skku.cs.android_pdf_viewer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    WebView webView;
    EditText urlEdit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        webView = (WebView)findViewById(R.id.webView);

        initWebView();

        urlEdit = (EditText) findViewById(R.id.urlEdit);
        urlEdit.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                switch (actionId){
                    case EditorInfo.IME_ACTION_DONE:
                    case EditorInfo.IME_ACTION_NEXT:
                    case EditorInfo.IME_ACTION_PREVIOUS:
                        webView.loadUrl(urlEdit.getText().toString());
                        return true;
                }
                return false;
            }
        });

    }

    public void initWebView() {
        webView.setWebViewClient(new WebViewClient() {
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url) {
                view.loadUrl(url);
                return true;
            }
        });
        WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webSettings.setAllowFileAccess(true);
        webSettings.setAllowFileAccessFromFileURLs(true);
        //webView.loadUrl("https://google.com/");
        //webView.loadUrl("file:///android_asset/test/sample.html");
        //webView.loadUrl("file:///android_asset/pdfjs/web/test.html");
        //webView.loadUrl("file:///android_asset/pdfjs/web/viewer.html?file=https://arxiv.org/pdf/2007.09389.pdf");
        //webView.loadUrl("https://sci-hub.se/10.1016/j.cviu.2021.103225");
        String pdf_path = "file:///android_asset/pdfjs/web/deep_pose.pdf";
        //webView.loadUrl("https://drive.google.com/viewerng/viewer?embedded=true&url=" + pdf_path);
        webView.loadUrl("file:///android_asset/test2/index.html");
    }

    @Override
    public void onBackPressed() {
        if (webView.canGoBack()) {
            webView.goBack();
        } else {
            super.onBackPressed();
        }
    }
}