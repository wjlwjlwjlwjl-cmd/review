package com.wjl.log.common.response;

import com.wjl.log.common.constant.ResultCode;

import lombok.Data;

@Data
public class Result<T> {
    private int code;
    private String errmsg;
    private T data;

    public static<T> Result<T> success(T data){
        Result<T> result = new Result<T>();
        result.data = data;
        result.code = ResultCode.SUCCESS.getCode();
        return result;
    }

    public static<T> Result<T> fail(String errmsg){
        Result<T> result = new Result<T> ();
        result.errmsg = errmsg;
        result.code = ResultCode.FAIL.getCode();
        return result;
    }
}
