#include "com_example_substrate_TestSub.h"
#include "cs.h"
#include "testlog.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <dlfcn.h>

#include <sys/types.h>
#include <unistd.h>


int (*orig_getaddrinfo)(const char *node, const char *service,
    const struct addrinfo *hints,
    struct addrinfo **res);


int (*orig_connect)(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);

int
(*orig_android_getaddrinfofornet) (const char *hostname, const char *servname,
    const struct addrinfo *hints, unsigned netid, unsigned mark, struct addrinfo **res);

int MyAndroid_getaddrinfofornet(const char *hostname, const char *servname,
    const struct addrinfo *hints, unsigned netid, unsigned mark, struct addrinfo **res)
{
    LOGI("in hook for net node =%s", hostname);
    return orig_android_getaddrinfofornet(hostname, servname, hints, netid, mark,res); 
}

int MyGetaddrinfo(const char *node, const char *service,
    const struct addrinfo *hints,
    struct addrinfo **res)
{
    LOGI("in hook MyGetaddrinfo node =%s",node);
    return orig_getaddrinfo(node,service, hints, res);
}

int MyConnect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen)
{
    LOGI("in hook MyConnect sockfd=%d",sockfd);
    return orig_connect(sockfd, addr,addrlen);
}

static pid_t (*old_getpid)();
static pid_t hook_getpid() {
//	pid_t pid = 0;
	old_getpid();
//	LOGI("in hook getpid ");
   return 0;
}

JNIEXPORT void JNICALL Java_com_example_substrate_TestSub_hookDemo
  (JNIEnv *, jobject)
{
    void* handle = dlopen("libc.so", RTLD_LAZY);
    void* android_getaddrinfofornet  = dlsym(handle, "android_getaddrinfofornet");
    dlclose(handle);

    LOGI("start hookDemo");

    MSHookFunction((void *)getpid, (void*)hook_getpid, (void **)&old_getpid);
    getpid();
    MSHookFunction((void *)connect, (void*)MyConnect, (void **)&orig_connect);
    MSHookFunction((void *)getaddrinfo, (void*)MyGetaddrinfo, (void **)&orig_getaddrinfo);
    LOGI("MyGetaddrinfo = %08x", MyGetaddrinfo);
    MSHookFunction((void *)android_getaddrinfofornet, (void*)MyAndroid_getaddrinfofornet, (void **)&orig_android_getaddrinfofornet);
    LOGI("end hookDemo");
}

