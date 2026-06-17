from langchain_openai import ChatOpenAI
import asyncio
from typing import Iterator
from langchain_core.output_parsers import StrOutputParser

model = ChatOpenAI(
    model="ark-code-latest"
)

def stream1():
    for chunk in model.stream("你好，我是谁？"):
        print(chunk.content, end="", flush=True)

async def stream2():
    async for chunk in model.astream("讲一个言情故事"):
        print(chunk.content, end="", flush=True)

def defined_parser(input: Iterator[str])-> Iterator[str]:
    buffer = ""
    for chunk in input:
        buffer += chunk
        while '，' in buffer or '。' in buffer:
            if '，' in buffer: 
                stop_index = buffer.index('，')
                yield buffer[:stop_index].strip()
                buffer = buffer[(stop_index + 1):]
            elif '。' in buffer:
                stop_index = buffer.index('。')
                yield buffer[:stop_index].strip()
                buffer = buffer[(stop_index + 1):]
    yield buffer.strip()

#asyncio.run(stream2())
parser = StrOutputParser()
chain = model | parser | defined_parser
for chunk in chain.stream("写一个关于爱情的诗歌"):
    print(chunk)