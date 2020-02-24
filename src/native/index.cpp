#include "napi.h"
#include <string>
#include "game/game_main.hpp"

// Arg0 - Json string
Napi::String Update(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() > 0) {
        Napi::TypeError::New(env, "Wrong number of arguments is Update()").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Error");
    }
    std::string data = info[0].ToString();
    return Napi::String::New(env, game_loop::update());
}

// Arg0 - Json string
Napi::String Signal(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments is Signal()").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Error");
    }
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Argument isn't a string in Signal()").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Error");
    }
    std::string data = info[0].ToString();
    return Napi::String::New(env, game_loop::signal(data));
}

// Callback for registering module with node.js
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "Update"),
        Napi::Function::New(env, Update)
    );
    exports.Set(
        Napi::String::New(env, "Signal"),
        Napi::Function::New(env, Signal)
    );
    return exports;
}


// Register 'naviteoop' module
NODE_API_MODULE(nativeoop, Init)