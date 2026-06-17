from langchain_openai import ChatOpenAI

llm = ChatOpenAI(
    model="ark-code-latest",
)

resp = llm.invoke("你是谁？简单介绍一下")
print(resp.content)