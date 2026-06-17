from langchain_core.tools import tool
from pydantic import BaseModel, Field
from typing_extensions import Annotated
from langchain_openai import ChatOpenAI
from langchain_core.messages import HumanMessage

@tool
def add(a: int, b: int):
    """
    add two num together
    Args:
        a: First Integer
        b: Second Integer
    Return:
        the sum of the two number
    """
    return a + b

class subInput(BaseModel):
    """this function gives the gap of the two val"""
    a: int = Field(..., description="first integer")
    b: int = Field(..., description="second integer")

@tool(args_schema=subInput)
def sub(a: int, b: int):
    return a - b;

@tool 
def multiply(a: Annotated[int, Field(..., description="first integer")], b: Annotated[int, Field(..., description="second integer")]):
    """multiple the two numbers"""
    return a * b

model = ChatOpenAI(
    model="ark-code-latest"
)
model_with_tool = model.bind_tools([add, sub, multiply])
msg_list = [HumanMessage("100 * 2等于多少?")]
ai_msgs = model_with_tool.invoke(msg_list)

for call in ai_msgs.tool_calls:
    tool = {"add": add, "sub": sub, "multiply": multiply}[call["name"]]
    tool_ret = tool.invoke(call)
    msg_list.append(tool_ret)

ret = model.invoke(msg_list)
print(ret.content)