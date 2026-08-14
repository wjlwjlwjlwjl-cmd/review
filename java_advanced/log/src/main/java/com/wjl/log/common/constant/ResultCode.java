package com.wjl.log.common.constant;

import lombok.AllArgsConstructor;
import lombok.Getter;

@AllArgsConstructor
public enum ResultCode {
    SUCCESS(200),
    FAIL(-1);
    @Getter
    private int code;
}
