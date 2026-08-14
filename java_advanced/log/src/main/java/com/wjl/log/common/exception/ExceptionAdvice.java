package com.wjl.log.common.exception;

import com.wjl.log.common.constant.ResultCode;
import com.wjl.log.common.response.Result;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import org.springframework.web.method.annotation.HandlerMethodValidationException;

@Slf4j
@RestControllerAdvice
public class ExceptionAdvice {
    @ExceptionHandler
    public Result<?> exceptionHandler(Exception e){
        log.error("error: ", e);
        Result<String> result = new Result<>();
        result.setErrmsg(e.getMessage());
        result.setCode(ResultCode.FAIL.getCode());
        return result;
    }

    @ResponseStatus(HttpStatus.BAD_REQUEST)
    @ExceptionHandler({HandlerMethodValidationException.class,
            MethodArgumentNotValidException.class})
    public Result<?> validationErrorHandler(Exception e){
        log.error("param validation error: ", e);
        return Result.fail("param validation error");
    }
}
