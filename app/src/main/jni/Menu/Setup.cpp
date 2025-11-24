#include <sstream>
#include "Menu/Menu.cpp"
#include "Menu/get_device_api_level_inlines.h"

void startActivityPermisson(JNIEnv *env, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jmethodID startActivity = env->GetMethodID(native_context, AY_OBFUSCATE("startActivity"),AY_OBFUSCATE("(Landroid/content/Intent;)V"));

    jmethodID pack = env->GetMethodID(native_context, AY_OBFUSCATE("getPackageName"),AY_OBFUSCATE("()Ljava/lang/String;"));
    auto packageName = reinterpret_cast<jstring>(env->CallObjectMethod(ctx, pack));

    const char *pkg = env->GetStringUTFChars(packageName, nullptr);

    std::stringstream pkgg;
    pkgg << AY_OBFUSCATE("package:");
    pkgg << pkg;
    std::string pakg = pkgg.str();

    jclass Uri = env->FindClass(AY_OBFUSCATE("android/net/Uri"));
    jmethodID Parce = env->GetStaticMethodID(Uri, AY_OBFUSCATE("parse"), AY_OBFUSCATE("(Ljava/lang/String;)Landroid/net/Uri;"));
    jobject UriMethod = env->CallStaticObjectMethod(Uri, Parce, env->NewStringUTF(pakg.c_str()));

    jclass intentclass = env->FindClass(AY_OBFUSCATE("android/content/Intent"));
    jmethodID newIntent = env->GetMethodID(intentclass, AY_OBFUSCATE("<init>"), AY_OBFUSCATE("(Ljava/lang/String;Landroid/net/Uri;)V"));
    jobject intent = env->NewObject(intentclass,newIntent,env->NewStringUTF(AY_OBFUSCATE("android.settings.action.MANAGE_OVERLAY_PERMISSION")), UriMethod);

    env->CallVoidMethod(ctx, startActivity, intent);
}

void startService(JNIEnv *env, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jclass intentClass = env->FindClass(AY_OBFUSCATE("android/content/Intent"));
    jclass actionString = env->FindClass(AY_OBFUSCATE("com/relgl/modmenu/Launcher"));
    jmethodID newIntent = env->GetMethodID(intentClass, AY_OBFUSCATE("<init>"), AY_OBFUSCATE("(Landroid/content/Context;Ljava/lang/Class;)V"));
    jobject intent = env->NewObject(intentClass,newIntent,ctx,actionString);
    jmethodID startActivityMethodId = env->GetMethodID(native_context, AY_OBFUSCATE("startService"), AY_OBFUSCATE("(Landroid/content/Intent;)Landroid/content/ComponentName;"));
    env->CallObjectMethod(ctx, startActivityMethodId, intent);
}

void *exit_thread(void *) {
    sleep(5);
    exit(0);
}

//Needed jclass parameter because this is a static java method
void CheckOverlayPermission(JNIEnv *env, jclass, jobject ctx){
    //If overlay permission option is greyed out, make sure to add android.permission.SYSTEM_ALERT_WINDOW in manifest

    LOGI(AY_OBFUSCATE("Check overlay permission"));

    int sdkVer = api_level();
    if (sdkVer >= 23){ //Android 6.0
        jclass Settings = env->FindClass(AY_OBFUSCATE("android/provider/Settings"));
        jmethodID canDraw =env->GetStaticMethodID(Settings, AY_OBFUSCATE("canDrawOverlays"), AY_OBFUSCATE("(Landroid/content/Context;)Z"));
        if (!env->CallStaticBooleanMethod(Settings, canDraw, ctx)){
            startActivityPermisson(env, ctx);

            pthread_t ptid;
            pthread_create(&ptid, nullptr, exit_thread, nullptr);
            return;
        }
    }


    LOGI(AY_OBFUSCATE("Start service"));

    //StartMod Normal
    startService(env, ctx);
}

void Init(JNIEnv *env, jobject, jobject ctx, jobject title, jobject subtitle, jobject t1, jobject t2, jobject t3, jobject t4){
    //Set sub title
    setText(env, title, AY_OBFUSCATE("<b>Developed by ReLGL Team</b>"));

    //Set sub title
    setText(env, subtitle, AY_OBFUSCATE("<b>Continuing the legacy of LGLTeam</b>"));

    setText(env, t1, AY_OBFUSCATE("Player<br>Mods"));

    setText(env, t2, AY_OBFUSCATE("Player<br>Abilties"));

    setText(env, t3, AY_OBFUSCATE("Account<br>Mods"));

    setText(env, t4, AY_OBFUSCATE("ReLGL<br>Project"));

    initValid = true;
}