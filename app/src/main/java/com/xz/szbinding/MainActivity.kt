package com.xz.szbinding

import android.content.Intent
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.os.Environment
import android.provider.Settings
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.xz.szbinding.databinding.ActivityMainBinding
import kotlin.concurrent.thread


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R
            && !Environment.isExternalStorageManager()
        ) {
            val intent = Intent(Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION)
            val uri = Uri.fromParts("package", packageName, null)
            intent.data = uri
            startActivity(intent)
        }

        binding = ActivityMainBinding.inflate(layoutInflater)

        setContentView(binding.root)

        binding.sampleText.setOnClickListener {
            thread {
                compress2(arrayOf(
                    "a",
                    "tzip",
                    "/storage/emulated/0/test4/wa.zip",
//                    "wz.zip",
                    "/storage/emulated/0/wz.apk"
                ))
                Log.d("com","-------ed-------");
            }

        }
        // Example of a call to a native method
    }

    /**
     * A native method that is implemented by the 'sz23binding' native library,
     * which is packaged with this application.
     */
    private external fun compress2(
        args: Array<String>,
    ): Int


    companion object {
        // Used to load the 'sz23binding' library on application startup.
        init {
            System.loadLibrary("szbinding")
        }
    }
}