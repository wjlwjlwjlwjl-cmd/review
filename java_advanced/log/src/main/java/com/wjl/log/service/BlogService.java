package com.wjl.log.service;

import com.wjl.log.dto.response.BlogInfoResponse;
import jakarta.validation.constraints.NotNull;

import java.util.List;

public interface BlogService {
    public List<BlogInfoResponse> getList();
    public BlogInfoResponse getDetail(@NotNull int blogId);
}
