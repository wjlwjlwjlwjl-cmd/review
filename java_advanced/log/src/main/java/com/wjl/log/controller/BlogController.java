package com.wjl.log.controller;

import com.wjl.log.dto.response.BlogInfoResponse;
import com.wjl.log.service.BlogService;
import com.wjl.log.service.impl.BlogServiceImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/blog")
public class BlogController {
    @Autowired
    BlogServiceImpl blogService;

    @RequestMapping("/getList")
    public List<BlogInfoResponse> getList(){
        return blogService.getList();
    }

    @RequestMapping("/getDetail")
    public BlogInfoResponse getDetail(@RequestParam int blogId){
        return blogService.getDetail(blogId);
    }
}
