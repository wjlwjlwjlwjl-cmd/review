package com.wjl.log.utils;

import io.jsonwebtoken.*;
import io.jsonwebtoken.io.Decoders;
import io.jsonwebtoken.security.Keys;
import lombok.extern.slf4j.Slf4j;

import javax.crypto.SecretKey;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

@Slf4j
public class JwtUtil {
    //密钥
    public static String secret =
            "dVnsmy+SIX6pNptQdeclDSJ26EMSPEIhvZYKBTTug4k=";
    private static long expiration = 60 * 60 * 24 * 1000;
    //生成安全密钥
    private static SecretKey secretKey = Keys.hmacShaKeyFor(Decoders.BASE64.decode(secret));

    public static String genJwt(Map<String, Object> claims){
        return Jwts
                .builder()
                .addClaims(claims)
                .setIssuedAt(new Date())
                .setExpiration(new Date(System.currentTimeMillis() + expiration))
                .signWith(secretKey)
                .compact();
    }

    public static Claims parseJwt(String jwt){
        //设置签名密钥
        JwtParserBuilder jwtParserBuilder = Jwts.parserBuilder().setSigningKey(secretKey);
        try{
            return jwtParserBuilder.build().parseClaimsJwt(jwt).getBody();
        }
        catch(Exception e){
            log.error("jwt 解析失败: " + e);
        }
        return null;
    }

    public static Integer getUserIdFromToken(String jwt){
        Claims claims = parseJwt(jwt);
        if(claims != null){
            Map<String, Object> map = new HashMap<>()
        }
    }
}
