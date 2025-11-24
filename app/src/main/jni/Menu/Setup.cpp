#include <sstream>
#include "Menu/Menu.cpp"
#include "Menu/get_device_api_level_inlines.h"

void Toast(JNIEnv *env, jobject thiz, const char *text, int length) {
    jstring jstr = env->NewStringUTF(text);
    jclass toast = env->FindClass(OBFUSCATE("android/widget/Toast"));
    jmethodID methodMakeText =env->GetStaticMethodID(toast,OBFUSCATE("makeText"),OBFUSCATE("(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;"));
    jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText,thiz, jstr, length);
    jmethodID methodShow = env->GetMethodID(toast, OBFUSCATE("show"), OBFUSCATE("()V"));
    env->CallVoidMethod(toastobj, methodShow);
}

void startActivityPermisson(JNIEnv *env, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jmethodID startActivity = env->GetMethodID(native_context, OBFUSCATE("startActivity"),OBFUSCATE("(Landroid/content/Intent;)V"));

    jmethodID pack = env->GetMethodID(native_context, OBFUSCATE("getPackageName"),OBFUSCATE("()Ljava/lang/String;"));
    auto packageName = reinterpret_cast<jstring>(env->CallObjectMethod(ctx, pack));

    const char *pkg = env->GetStringUTFChars(packageName, nullptr);

    std::stringstream pkgg;
    pkgg << OBFUSCATE("package:");
    pkgg << pkg;
    std::string pakg = pkgg.str();

    jclass Uri = env->FindClass(OBFUSCATE("android/net/Uri"));
    jmethodID Parce = env->GetStaticMethodID(Uri, OBFUSCATE("parse"), OBFUSCATE("(Ljava/lang/String;)Landroid/net/Uri;"));
    jobject UriMethod = env->CallStaticObjectMethod(Uri, Parce, env->NewStringUTF(pakg.c_str()));

    jclass intentclass = env->FindClass(OBFUSCATE("android/content/Intent"));
    jmethodID newIntent = env->GetMethodID(intentclass, OBFUSCATE("<init>"), OBFUSCATE("(Ljava/lang/String;Landroid/net/Uri;)V"));
    jobject intent = env->NewObject(intentclass,newIntent,env->NewStringUTF(OBFUSCATE("android.settings.action.MANAGE_OVERLAY_PERMISSION")), UriMethod);

    env->CallVoidMethod(ctx, startActivity, intent);
}

void startService(JNIEnv *env, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jclass intentClass = env->FindClass(OBFUSCATE("android/content/Intent"));
    jclass actionString = env->FindClass(OBFUSCATE("com/relgl/modmenu/Launcher"));
    jmethodID newIntent = env->GetMethodID(intentClass, OBFUSCATE("<init>"), OBFUSCATE("(Landroid/content/Context;Ljava/lang/Class;)V"));
    jobject intent = env->NewObject(intentClass,newIntent,ctx,actionString);
    jmethodID startActivityMethodId = env->GetMethodID(native_context, OBFUSCATE("startService"), OBFUSCATE("(Landroid/content/Intent;)Landroid/content/ComponentName;"));
    env->CallObjectMethod(ctx, startActivityMethodId, intent);
}

void *exit_thread(void *) {
    sleep(5);
    exit(0);
}

//Needed jclass parameter because this is a static java method
void CheckOverlayPermission(JNIEnv *env, jclass, jobject ctx){
    //If overlay permission option is greyed out, make sure to add android.permission.SYSTEM_ALERT_WINDOW in manifest

    LOGI(OBFUSCATE("Check overlay permission"));

    int sdkVer = api_level();
    if (sdkVer >= 23){ //Android 6.0
        jclass Settings = env->FindClass(OBFUSCATE("android/provider/Settings"));
        jmethodID canDraw =env->GetStaticMethodID(Settings, OBFUSCATE("canDrawOverlays"), OBFUSCATE("(Landroid/content/Context;)Z"));
        if (!env->CallStaticBooleanMethod(Settings, canDraw, ctx)){
            Toast(env,ctx,OBFUSCATE("Overlay permission is required in order to show mod menu."),1);
            Toast(env,ctx,OBFUSCATE("Overlay permission is required in order to show mod menu."),1);
            startActivityPermisson(env, ctx);

            pthread_t ptid;
            pthread_create(&ptid, nullptr, exit_thread, nullptr);
            return;
        }
    }


    LOGI(OBFUSCATE("Start service"));

    //StartMod Normal
    startService(env, ctx);
}

void Init(JNIEnv *env, jobject, jobject ctx, jobject title, jobject subtitle, jobject t1, jobject t2, jobject t3, jobject t4){
    //Set sub title
    setText(env, title, OBFUSCATE("<b>Developed by ReLGL Team</b>"));

    //Set sub title
    setText(env, subtitle, OBFUSCATE("<b>Among Us</b>"));

    setText(env, t1, OBFUSCATE("Player<br>Mods"));

    setText(env, t2, OBFUSCATE("Player<br>Abilties"));

    setText(env, t3, OBFUSCATE("Account<br>Mods"));

    setText(env, t4, OBFUSCATE("ReLGL"));

    //Toast Example
    Toast(env,ctx,OBFUSCATE("Developed by ReLGL Team"),ToastLength::LENGTH_LONG);

    initValid = true;
}