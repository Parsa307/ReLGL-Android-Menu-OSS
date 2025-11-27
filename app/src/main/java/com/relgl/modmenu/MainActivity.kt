/* package com.relgl.modmenu;

import android.annotation.SuppressLint;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.widget.LinearLayout;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.os.Handler;

public class MainActivity extends Activity

{

    // Only if you have changed MainActivity to yours and you want to call game's activity.
    val GameActivity = "com.unity3d.player.UnityPlayerActivity";
    val hasLaunched = false;

    //To call onCreate, please refer to README.md
    @SuppressLint("SetTextI18n")
    @Override
    protected onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //To launch game activity
        if (!hasLaunched) {
            try {
                //Start service
                hasLaunched = true;
                //Launch mod menu.
                MainActivity.this.startActivity(new Intent(MainActivity.this, Class.forName(MainActivity.this.GameActivity)));
                Main.Start(this);
                return;
            } catch (ClassNotFoundException e) {
                Log.e("Mod_menu", "Error. Game's main activity does not exist");
            }
        }

        //Launch mod menu.
        Main.Start(this);
       // Main.StartWithoutPermission(this);
    }
} */

package com.relgl.modmenu

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.util.Log

class MainActivity : Activity() {

    // Only if you changed MainActivity and want to call the game’s activity
    private val gameActivity = "com.unity3d.player.UnityPlayerActivity"
    private var hasLaunched = false

    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Launch game activity
        if (!hasLaunched) {
            try {
                hasLaunched = true

                // Launch game activity
                val intent = Intent(this, Class.forName(gameActivity))
                startActivity(intent)

                // Launch mod menu
                Main.Start(this)
                return

            } catch (e: ClassNotFoundException) {
                Log.e("Mod_menu", "Error. Game's main activity does not exist.")
            }
        }

        // Launch mod menu normally
        Main.Start(this)
        // Main.StartWithoutPermission(this)
    }
}
