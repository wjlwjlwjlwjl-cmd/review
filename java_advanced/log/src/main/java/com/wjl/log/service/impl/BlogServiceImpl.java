package com.wjl.log.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.wjl.log.dto.response.BlogInfoResponse;
import com.wjl.log.entity.BlogInfo;
import com.wjl.log.mapper.BlogMapper;
import com.wjl.log.service.BlogService;
import jakarta.validation.constraints.NotNull;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class BlogServiceImpl implements BlogService {
    @Autowired
    BlogMapper blogMapper;

    @Override
    public List<BlogInfoResponse> getList(){
        LambdaQueryWrapper<BlogInfo> lambdaQueryWrapper
                = new LambdaQueryWrapper<BlogInfo>()
                .eq(BlogInfo::getDeleteFlag, 0)
                .orderByDesc(BlogInfo::getId);

        return blogMapper.selectList(lambdaQueryWrapper)
            .stream().map(blogEntity -> {
                BlogInfoResponse blogInfoResponse = new BlogInfoResponse();
                BeanUtils.copyProperties(blogEntity, blogInfoResponse);
                return blogInfoResponse;
            }).toList();
    }

    @Override
    public BlogInfoResponse getDetail(@NotNull int blogId) {
        BlogInfo blogInfo = blogMapper.selectOne(new LambdaQueryWrapper<BlogInfo>().eq(BlogInfo::getId, blogId).eq(BlogInfo::getDeleteFlag, 0));
        BlogInfoResponse blogInfoResponse = new BlogInfoResponse();
        BeanUtils.copyProperties(blogInfo, blogInfoResponse);
        return blogInfoResponse;
    }
}
