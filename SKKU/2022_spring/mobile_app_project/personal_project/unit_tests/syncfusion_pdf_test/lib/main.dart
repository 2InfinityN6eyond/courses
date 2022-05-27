import 'package:flutter/material.dart';
import 'package:syncfusion_flutter_pdfviewer/pdfviewer.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  late PdfViewerController _pdfViewerController;
  @override
  void initState(){
    _pdfViewerController = PdfViewerController();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    print("building...");
    return SafeArea(
        child: Scaffold(
          body: SfPdfViewer.network(
            'https://reader.elsevier.com/reader/sd/pii/S1077314221000692?token=A9363A92A00E9A880BAC0131F4048A2A8AFB5A2865CFDDBE2FE050F040C37529B06F999902FFBD71C120747F3B47206D&originRegion=us-east-1&originCreation=20220523143542',
          //controller: _pdfViewerController,
          ),
        )
    );
  }
}
