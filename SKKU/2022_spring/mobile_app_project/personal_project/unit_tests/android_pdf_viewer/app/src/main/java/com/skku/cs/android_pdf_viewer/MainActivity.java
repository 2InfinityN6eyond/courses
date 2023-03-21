package com.skku.cs.android_pdf_viewer;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.webkit.ValueCallback;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.EditText;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {

    ValueCallback mFilePathCallback = null;

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
         webSettings.setAllowFileAccess(true);
        webSettings.setAllowFileAccessFromFileURLs(true);


        webView.setWebChromeClient(new WebChromeClient() {
            @Override
            public boolean onShowFileChooser(WebView webView, ValueCallback filePathCallback, WebChromeClient.FileChooserParams fileChooserParams) {
                mFilePathCallback = filePathCallback;

                Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
                intent.addCategory(Intent.CATEGORY_OPENABLE);
                intent.setType("image/*");

            // 파일 n개 선택 가능하도록 처리
            intent.putExtra(Intent.EXTRA_ALLOW_MULTIPLE, true);

            startActivityForResult(intent, 0);
            return true;
        }
    });  

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

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        Log.e("resultCode:: ", String.valueOf(resultCode));
        if (requestCode == 0 && resultCode == Activity.RESULT_OK) {

            // 파일 n개 선택한 경우
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN && data != null && data.getClipData() != null && data.getClipData().getItemCount() > 0) {
                int count = data.getClipData().getItemCount();

                Uri[] uriArr = new Uri[count];
                for (int i=0; i<count; i++) {
                    uriArr[i] = data.getClipData().getItemAt(i).getUri();
                }

                mFilePathCallback.onReceiveValue(uriArr);

            } else if (data != null && data.getData() != null) {
                // 파일 1개 선택한 경우
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                    mFilePathCallback.onReceiveValue(WebChromeClient.FileChooserParams.parseResult(resultCode, data));
                } else {
                    mFilePathCallback.onReceiveValue(new Uri[]{data.getData()});
                }
            }

            mFilePathCallback = null;

        } else {
            mFilePathCallback.onReceiveValue(null);
        }
    }

}


