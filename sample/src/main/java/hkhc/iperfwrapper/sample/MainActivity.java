package hkhc.iperfwrapper.sample;

import android.os.Handler;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;
import java.io.IOException;

import hkhc.iperfwrapper.AndroidDefaults;
import hkhc.iperfwrapper.Iperf3;
import hkhc.iperfwrapper.IperfException;
import hkhc.iperfwrapper.R;
import hkhc.utils.FileUtils;

public class MainActivity extends AppCompatActivity {


    private Handler handler = new Handler();
    Iperf3 perf3 = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button b = (Button) findViewById(R.id.button);
        new File(MainActivity.this.getCacheDir() + "/output.txt").delete();

//        RunTimePermissions.verifyStoragePermissions(this);
        b.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new Thread() {

                    public void run() {

                        try {

                            perf3 = new Iperf3().newTest()
                                    .logError()
                                    .defaults(new AndroidDefaults(MainActivity.this))
                                    .testRole(Iperf3.ROLE_CLIENT)
                                    .hostname("206.189.110.112")
                                    .port(5201)
                                    .durationInSeconds(5)
                                    .numberOfStreams(30)
                                    .reverse(true)
                                    .logfile(MainActivity.this.getCacheDir() + "/output.txt")
                                    .outputJson(true)
                                    .runClient();


                            handler.post(new Runnable() {
                                public void run() {

                                    Log.e("TEST", "RESPONSE: " + MainActivity.this.getCacheDir() + "/output.txt");
                                    TextView tv = (TextView) findViewById(R.id.editResult);
                                    try {
                                        String result = FileUtils.readFileToString(MainActivity.this.getCacheDir() + "/output.txt");
                                        tv.setText(result);
                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    }
                                }
                            });


                        } catch (IperfException e) {
                            e.printStackTrace();
                        } finally {
                            perf3.freeTest();
                        }
                    }
                }.start();

            }
        });
    }
}
