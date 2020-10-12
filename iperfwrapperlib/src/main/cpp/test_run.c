//
// Created by Herman Cheung on 6/3/2017.
//

#include <jni.h>
#include <stdio.h>
#include <sys/select.h>
#include <android/log.h>
#include <string.h>
#include "../../../iperf/src/iperf_api.h"
#include "../../../iperf/src/iperf.h"

JNIEXPORT jlong JNICALL
Java_hkhc_iperfwrapper_Iperf3_newTestImpl( JNIEnv* env, jobject thiz )
{

    struct iperf_test *test;
    test = iperf_new_test();
    __android_log_print(ANDROID_LOG_DEBUG, "IPERF", "new test %lld", (long long)test);

    return (jlong)test;

}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_freeTestImpl( JNIEnv* env, jobject thiz, jlong ref)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    iperf_free_test(test);

}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_testRoleImpl( JNIEnv* env, jobject thiz, jlong ref, jchar role)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    __android_log_print(ANDROID_LOG_DEBUG, "IPERF", "set role %c %lld", (char)role, 'c');

    iperf_set_test_role(test, (char)role );

}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_defaultsImpl( JNIEnv* env, jobject thiz, jlong ref)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    iperf_defaults(test);

}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_hostnameImpl( JNIEnv* env, jobject thiz, jlong ref, jstring j_hostname)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    const char *hostname = (*env)->GetStringUTFChars(env, j_hostname, 0);

    iperf_set_test_server_hostname(test, (char *) hostname);

    (*env)->ReleaseStringUTFChars(env, j_hostname, hostname);


}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_tempFileTemplateImpl( JNIEnv* env, jobject thiz, jlong ref, jstring j_template)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    const char *template = (*env)->GetStringUTFChars(env, j_template, 0);

    iperf_set_test_template(test, (char *) template);

    (*env)->ReleaseStringUTFChars(env, j_template, template);


}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_durationImpl( JNIEnv* env, jobject thiz, jlong ref, jint duration)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    iperf_set_test_duration(test, duration);


}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_portImpl( JNIEnv* env, jobject thiz, jlong ref, jint port)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    iperf_set_test_server_port(test, port);


}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_numberOfStreamsImpl( JNIEnv* env, jobject thiz, jlong ref, jint streams)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    iperf_set_test_num_streams(test, streams);


}

char *error = NULL;

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_logErrorImpl( JNIEnv* env, jobject thiz)
{

    iperf_strerror(i_errno);

    iperf_err(NULL, "create new test error - %s", error);

}


JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_reverseImpl( JNIEnv* env, jobject thiz, jlong ref, jboolean reverse)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;
    iperf_set_test_reverse(test, reverse);
}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_runClientImpl( JNIEnv* env, jobject thiz, jlong ref)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    test->outfile = fopen(test->logfile, "a+");
    int x = iperf_run_client(test);
    __android_log_print(ANDROID_LOG_ERROR, "IPERF", "iperf_run_client return: %d", x);
    __android_log_print(ANDROID_LOG_ERROR, "IPERF", "output file: %s", (char *) test->outfile);

    if (x < 0) {
        error = iperf_strerror(i_errno);
        iperf_err(test, "error - %s", error);
        __android_log_print(ANDROID_LOG_ERROR, "IPERF", "error: %s", error);

    }

}

JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_outputJsonImpl( JNIEnv* env, jobject thiz, jlong ref, jboolean useJson)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    iperf_set_test_json_output(ref, (int)useJson);

}

/*
 * Command line options
 */


// OPT_LOG
JNIEXPORT void JNICALL
Java_hkhc_iperfwrapper_Iperf3_logFileImpl( JNIEnv* env, jobject thiz, jlong ref, jstring j_logfile)
{

    struct iperf_test *test;
    test = (struct iperf_test *)ref;

    const char *logfile = (*env)->GetStringUTFChars(env, j_logfile, 0);

    test->logfile = strdup(logfile);

    (*env)->ReleaseStringUTFChars(env, j_logfile, logfile);


}


