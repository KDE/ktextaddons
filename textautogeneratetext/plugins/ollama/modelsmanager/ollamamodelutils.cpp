/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelutils.h"
using namespace Qt::Literals::StringLiterals;

#include "autogeneratetext_ollama_debug.h"
#include <KLocalizedString>
#include <QMap>

QString OllamaModelUtils::description(const QString &modelName)
{
    static QMap<QString, QString> listTranslation = {
        {u"llama3.3"_s, i18n("New state of the art 70B model. Llama 3.3 70B offers similar performance compared to the Llama 3.1 405B model.")},
        {u"qwq"_s, i18n("QwQ is the reasoning model of the Qwen series.")},
        {u"llama3.2-vision"_s, i18n("Llama 3.2 Vision is a collection of instruction-tuned image reasoning generative models in 11B and 90B sizes.")},
        {u"llama3.2"_s, i18n("Meta's Llama 3.2 goes small with 1B and 3B models.")},
        {u"llama3.1"_s, i18n("Llama 3.1 is a new state-of-the-art model from Meta available in 8B, 70B and 405B parameter sizes.")},
        {u"llama3"_s, i18n("Meta Llama 3: The most capable openly available LLM to date")},
        {u"mistral"_s, i18n("The 7B model released by Mistral AI, updated to version 0.3.")},
        {u"nomic-embed-text"_s, i18n("A high-performing open embedding model with a large token context window.")},
        {u"gemma"_s, i18n("Gemma is a family of lightweight, state-of-the-art open models built by Google DeepMind. Updated to version 1.1")},
        {u"qwen"_s, i18n("Qwen 1.5 is a series of large language models by Alibaba Cloud spanning from 0.5B to 110B parameters")},
        {u"qwen2"_s, i18n("Qwen2 is a new series of large language models from Alibaba group")},
        {u"phi3"_s, i18n("Phi-3 is a family of lightweight 3B (Mini) and 14B (Medium) state-of-the-art open models by Microsoft.")},
        {u"llama2"_s, i18n("Llama 2 is a collection of foundation language models ranging from 7B to 70B parameters.")},
        {u"qwen2.5"_s,
         i18n("Qwen2.5 models are pretrained on Alibaba's latest large-scale dataset, encompassing up to 18 trillion tokens. The model supports up to 128K "
              "tokens and has multilingual support.")},
        {u"gemma2"_s, i18n("Google Gemma 2 is a high-performing and efficient model available in three sizes: 2B, 9B, and 27B.")},
        {u"llava"_s,
         i18n("LLaVA is a novel end-to-end trained large multimodal model that combines a vision encoder and Vicuna for general-purpose visual and language "
              "understanding. Updated to version 1.6.")},
        {u"codellama"_s, i18n("A large language model that can use text prompts to generate and discuss code.")},
        {u"qwen2.5-coder"_s,
         i18n("The latest series of Code-Specific Qwen models, with significant improvements in code generation, code reasoning, and code fixing.")},
        {u"mistral-nemo"_s, i18n("A state-of-the-art 12B model with 128k context length, built by Mistral AI in collaboration with NVIDIA.")},
        {u"tinyllama"_s, i18n("The TinyLlama project is an open endeavor to train a compact 1.1B Llama model on 3 trillion tokens.")},
        {u"mxbai-embed-large"_s, i18n("State-of-the-art large embedding model from mixedbread.ai")},
        {u"starcoder2"_s,
         i18n("StarCoder2 is the next generation of transparently trained open code LLMs that comes in three sizes: 3B, 7B and 15B parameters.")},
        {u"mixtral"_s, i18n("A set of Mixture of Experts (MoE) model with open weights by Mistral AI in 8x7b and 8x22b parameter sizes.")},
        {u"dolphin-mixtral"_s,
         i18n("Uncensored, 8x7b and 8x22b fine-tuned models based on the Mixtral mixture of experts models that excels at coding tasks. Created by Eric "
              "Hartford.")},
        {u"codegemma"_s,
         i18n("CodeGemma is a collection of powerful, lightweight models that can perform a variety of coding tasks like fill-in-the-middle code completion, "
              "code generation, natural language understanding, mathematical reasoning, and instruction following.")},
        {u"deepseek-coder-v2"_s,
         i18n("An open-source Mixture-of-Experts code language model that achieves performance comparable to GPT4-Turbo in code-specific tasks.")},
        {u"phi"_s, i18n("Phi-2: a 2.7B language model by Microsoft Research that demonstrates outstanding reasoning and language understanding capabilities.")},
        {u"llama2-uncensored"_s, i18n("Uncensored Llama 2 model by George Sung and Jarrad Hope.")},
        {u"deepseek-coder"_s, i18n("DeepSeek Coder is a capable coding model trained on two trillion code and natural language tokens.")},
        {u"snowflake-arctic-embed"_s, i18n("A suite of text embedding models by Snowflake, optimized for performance.")},
        {u"wizardlm2"_s,
         i18n("State of the art large language model from Microsoft AI with improved performance on complex chat, multilingual, reasoning and agent use "
              "cases.")},
        {u"dolphin-mistral"_s, i18n("The uncensored Dolphin model based on Mistral that excels at coding tasks. Updated to version 2.8.")},
        {u"dolphin-llama3"_s,
         i18n("Dolphin 2.9 is a new model with 8B and 70B sizes by Eric Hartford based on Llama 3 that has a variety of instruction, conversational, and "
              "coding skills.")},
        {u"yi"_s, i18n("Yi 1.5 is a high-performing, bilingual language model.")},
        {u"command-r"_s, i18n("Command R is a Large Language Model optimized for conversational interaction and long context tasks.")},
        {u"orca-mini"_s, i18n("A general-purpose model ranging from 3 billion parameters to 70 billion, suitable for entry-level hardware.")},
        {u"llava-llama3"_s, i18n("A LLaVA model fine-tuned from Llama 3 Instruct with better scores in several benchmarks.")},
        {u"zephyr"_s, i18n("Zephyr is a series of fine-tuned versions of the Mistral and Mixtral models that are trained to act as helpful assistants.")},
        {u"phi3.5"_s, i18n("A lightweight AI model with 3.8 billion parameters with performance overtaking similarly and larger sized models.")},
        {u"all-minilm"_s, i18n("Embedding models on very large sentence level datasets.")},
        {u"codestral"_s, i18n("Codestral is Mistral AI’s first-ever code model designed for code generation tasks.")},
        {u"starcoder"_s, i18n("StarCoder is a code generation model trained on 80+ programming languages.")},
        {u"vicuna"_s, i18n("General use chat model based on Llama and Llama 2 with 2K to 16K context sizes.")},
        {u"granite-code"_s, i18n("A family of open foundation models by IBM for Code Intelligence")},
        {u"mistral-openorca"_s, i18n("Mistral OpenOrca is a 7 billion parameter model, fine-tuned on top of the Mistral 7B model using the OpenOrca dataset.")},
        {u"smollm"_s, i18n("A family of small models with 135M, 360M, and 1.7B parameters, trained on a new high-quality dataset.")},
        {u"wizard-vicuna-uncensored"_s, i18n("Wizard Vicuna Uncensored is a 7B, 13B, and 30B parameter model based on Llama 2 uncensored by Eric Hartford.")},
        {u"llama2-chinese"_s, i18n("Llama 2 based model fine tuned to improve Chinese dialogue ability.")},
        {u"bge-m3"_s,
         i18n("BGE-M3 is a new model from BAAI distinguished for its versatility in Multi-Functionality, Multi-Linguality, and Multi-Granularity.")},
        {u"codegeex4"_s, i18n("A versatile model for AI software development scenarios, including code completion.")},
        {u"openchat"_s,
         i18n("A family of open-source models trained on a wide variety of data, surpassing ChatGPT on various benchmarks. Updated to version 3.5-0106.")},
        {u"aya"_s, i18n("Aya 23, released by Cohere, is a new family of state-of-the-art, multilingual models that support 23 languages.")},
        {u"codeqwen"_s, i18n("CodeQwen1.5 is a large language model pretrained on a large amount of code data.")},
        {u"nous-hermes2"_s, i18n("The powerful family of models by Nous Research that excels at scientific discussion and coding tasks.")},
        {u"command-r-plus"_s, i18n("Command R+ is a powerful, scalable large language model purpose-built to excel at real-world enterprise use cases.")},
        {u"wizardcoder"_s, i18n("State-of-the-art code generation model")},
        {u"stable-code"_s,
         i18n("Stable Code 3B is a coding model with instruct and code completion variants on par with models such as Code Llama 7B that are 2.5x larger.")},
        {u"tinydolphin"_s, i18n("An experimental 1.1B parameter model trained on the new Dolphin 2.8 dataset by Eric Hartford and based on TinyLlama.")},
        {u"openhermes"_s, i18n("OpenHermes 2.5 is a 7B model fine-tuned by Teknium on Mistral with fully open datasets.")},
        {u"mistral-large"_s,
         i18n("Mistral Large 2 is Mistral's new flagship model that is significantly more capable in code generation, mathematics, and reasoning with 128k "
              "context window and support for dozens of languages.")},
        {u"qwen2-math"_s,
         i18n("Qwen2 Math is a series of specialized math language models built upon the Qwen2 LLMs, which significantly outperforms the mathematical "
              "capabilities of open-source models and even closed-source models (e.g., GPT4o).")},
        {u"glm4"_s, i18n("A strong multi-lingual general language model with competitive performance to Llama 3.")},
        {u"stablelm2"_s,
         i18n("Stable LM 2 is a state-of-the-art 1.6B and 12B parameter language model trained on multilingual data in English, Spanish, German, Italian, "
              "French, Portuguese, and Dutch.")},
        {u"bakllava"_s, i18n("BakLLaVA is a multimodal model consisting of the Mistral 7B base model augmented with the LLaVA architecture.")},
        {u"reflection"_s,
         i18n("A high-performing model trained with a new technique called Reflection-tuning that teaches a LLM to detect mistakes in its reasoning and "
              "correct course.")},
        {u"deepseek-llm"_s, i18n("An advanced language model crafted with 2 trillion bilingual tokens.")},
        {u"llama3-gradient"_s, i18n("This model extends LLama-3 8B's context length from 8k to over 1m tokens.")},
        {u"wizard-math"_s, i18n("Model focused on math and logic problems")},
        {u"moondream"_s, i18n("moondream2 is a small vision language model designed to run efficiently on edge devices.")},
        {u"neural-chat"_s, i18n("A fine-tuned model based on Mistral with good coverage of domain and language.")},
        {u"llama3-chatqa"_s,
         i18n("A model from NVIDIA based on Llama 3 that excels at conversational question answering (QA) and retrieval-augmented generation (RAG).")},
        {u"xwinlm"_s, i18n("Conversational model based on Llama 2 that performs competitively on various benchmarks.")},
        {u"sqlcoder"_s, i18n("SQLCoder is a code completion model fined-tuned on StarCoder for SQL generation tasks")},
        {u"nous-hermes"_s, i18n("General use models based on Llama and Llama 2 from Nous Research.")},
        {u"phind-codellama"_s, i18n("Code generation model based on Code Llama.")},
        {u"yarn-llama2"_s, i18n("An extension of Llama 2 that supports a context of up to 128k tokens.")},
        {u"dolphincoder"_s, i18n("A 7B and 15B uncensored variant of the Dolphin model family that excels at coding, based on StarCoder2.")},
        {u"wizardlm"_s, i18n("General use model based on Llama 2.")},
        {u"deepseek-v2"_s, i18n("A strong, economical, and efficient Mixture-of-Experts language model.")},
        {u"starling-lm"_s,
         i18n("Starling is a large language model trained by reinforcement learning from AI feedback focused on improving chatbot helpfulness.")},
        {u"samantha-mistral"_s, i18n("A companion assistant trained in philosophy, psychology, and personal relationships. Based on Mistral.")},
        {u"hermes3"_s, i18n("Hermes 3 is the latest version of the flagship Hermes series of LLMs by Nous Research")},
        {u"yi-coder"_s,
         i18n("Yi-Coder is a series of open-source code language models that delivers state-of-the-art coding performance with fewer than 10 billion "
              "parameters.")},
        {u"falcon"_s,
         i18n("A large language model built by the Technology Innovation Institute (TII) for use in summarization, text generation, and chat bots.")},
        {u"internlm2"_s, i18n("InternLM2.5 is a 7B parameter model tailored for practical scenarios with outstanding reasoning capability.")},
        {u"solar"_s, i18n("A compact, yet powerful 10.7B large language model designed for single-turn conversation.")},
        {u"athene-v2"_s, i18n("Athene-V2 is a 72B parameter model which excels at code completion, mathematics, and log extraction tasks.")},
        {u"llava-phi3"_s, i18n("A new small LLaVA model fine-tuned from Phi 3 Mini.")},
        {u"orca2"_s,
         i18n("Orca 2 is built by Microsoft research, and are a fine-tuned version of Meta's Llama 2 models. The model is designed to excel particularly in "
              "reasoning.")},
        {u"minicpm-v"_s, i18n("A series of multimodal LLMs (MLLMs) designed for vision-language understanding.")},
        {u"stable-beluga"_s, i18n("Llama 2 based model fine tuned on an Orca-style dataset. Originally called Free Willy.")},
        {u"mistral-small"_s, i18n("Mistral Small 3 sets a new benchmark in the “small” Large Language Models category below 70B.")},
        {u"dolphin-phi"_s, i18n("2.7B uncensored Dolphin model by Eric Hartford, based on the Phi language model by Microsoft Research.")},
        {u"smollm2"_s, i18n("SmolLM2 is a family of compact language models available in three size: 135M, 360M, and 1.7B parameters.")},
        {u"wizardlm-uncensored"_s, i18n("Uncensored version of Wizard LM model")},
        {u"nemotron-mini"_s, i18n("A commercial-friendly small language model by NVIDIA optimized for roleplay, RAG QA, and function calling.")},
        {u"yarn-mistral"_s, i18n("An extension of Mistral to support context windows of 64K or 128K.")},
        {u"llama-pro"_s,
         i18n("An expansion of Llama 2 that specializes in integrating both general language understanding and domain-specific knowledge, particularly in "
              "programming and mathematics.")},
        {u"medllama2"_s, i18n("Fine-tuned Llama 2 model to answer medical questions based on an open source medical dataset.")},
        {u"meditron"_s, i18n("Open-source medical large language model adapted from Llama 2 to the medical domain.")},
        {u"llama3-groq-tool-use"_s,
         i18n("A series of models from Groq that represent a significant advancement in open-source AI capabilities for tool use/function calling.")},
        {u"nemotron"_s,
         i18n("Llama-3.1-Nemotron-70B-Instruct is a large language model customized by NVIDIA to improve the helpfulness of LLM generated responses to user "
              "queries.")},
        {u"nexusraven"_s, i18n("Nexus Raven is a 13B instruction tuned model for function calling tasks.")},
        {u"nous-hermes2-mixtral"_s, i18n("The Nous Hermes 2 model from Nous Research, now trained over Mixtral.")},
        {u"codeup"_s, i18n("Great code generation model based on Llama2.")},
        {u"everythinglm"_s, i18n("Uncensored Llama2 based model with support for a 16K context window.")},
        {u"granite3-dense"_s,
         i18n("The IBM Granite 2B and 8B models are designed to support tool-based use cases and support for retrieval augmented generation (RAG), "
              "streamlining code generation, translation and bug fixing.")},
        {u"magicoder"_s,
         i18n("Magicoder is a family of 7B parameter models trained on 75K synthetic instruction data using OSS-Instruct, a novel approach to enlightening "
              "LLMs with open-source code snippets.")},
        {u"stablelm-zephyr"_s, i18n("A lightweight chat model allowing accurate, and responsive output without requiring high-end hardware.")},
        {u"codebooga"_s, i18n("A high-performing code instruct model created by merging two existing code models.")},
        {u"falcon2"_s, i18n("Falcon2 is an 11B parameters causal decoder-only model built by TII and trained over 5T tokens.")},
        {u"wizard-vicuna"_s, i18n("Wizard Vicuna is a 13B parameter model based on Llama 2 trained by MelodysDreamj.")},
        {u"mistrallite"_s, i18n("MistralLite is a fine-tuned model based on Mistral with enhanced capabilities of processing long contexts.")},
        {u"mathstral"_s, i18n("MathΣtral: a 7B model designed for math reasoning and scientific discovery by Mistral AI.")},
        {u"duckdb-nsql"_s, i18n("7B parameter text-to-SQL model made by MotherDuck and Numbers Station.")},
        {u"megadolphin"_s, i18n("MegaDolphin-2.2-120b is a transformation of Dolphin-2.2-70b created by interleaving the model with itself.")},
        {u"solar-pro"_s, i18n("Solar Pro Preview: an advanced large language model (LLM) with 22 billion parameters designed to fit into a single GPU")},
        {u"reader-lm"_s, i18n("A series of models that convert HTML content to Markdown content, which is useful for content conversion tasks.")},
        {u"notux"_s, i18n("A top-performing mixture of experts model, fine-tuned with high-quality data.")},
        {u"notus"_s, i18n("A 7B chat model fine-tuned with high-quality data and based on Zephyr.")},
        {u"open-orca-platypus2"_s, i18n("Merge of the Open Orca OpenChat model and the Garage-bAInd Platypus 2 model. Designed for chat and code generation.")},
        {u"goliath"_s, i18n("A language model created by combining two fine-tuned Llama 2 70B models into one.")},
        {u"granite3-moe"_s,
         i18n("The IBM Granite 1B and 3B models are the first mixture of experts (MoE) Granite models from IBM designed for low latency usage.")},
        {u"nuextract"_s, i18n("A 3.8B model fine-tuned on a private high-quality synthetic dataset for information extraction, based on Phi-3.")},
        {u"aya-expanse"_s, i18n("Cohere For AI's language models trained to perform well across 23 different languages.")},
        {u"dbrx"_s, i18n("DBRX is an open, general-purpose LLM created by Databricks.")},
        {u"marco-o1"_s, i18n("An open large reasoning model for real-world solutions by the Alibaba International Digital Commerce Group (AIDC-AI).")},
        {u"bge-large"_s, i18n("Embedding model from BAAI mapping texts to vectors.")},
        {u"firefunction-v2"_s, i18n("An open weights function calling model based on Llama 3, competitive with GPT-4o function calling capabilities.")},
        {u"alfred"_s, i18n("A robust conversational model designed to be used for both chat and instruct use cases.")},
        {u"deepseek-v2.5"_s,
         i18n("An upgraded version of DeekSeek-V2 that integrates the general and coding abilities of both DeepSeek-V2-Chat and DeepSeek-Coder-V2-Instruct.")},
        {u"shieldgemma"_s,
         i18n("ShieldGemma is set of instruction tuned models for evaluating the safety of text prompt input and text output responses against a set of "
              "defined safety policies.")},
        {u"bespoke-minicheck"_s, i18n("A state-of-the-art fact-checking model developed by Bespoke Labs.")},
        {u"llama-guard3"_s, i18n("Llama Guard 3 is a series of models fine-tuned for content safety classification of LLM inputs and responses.")},
        {u"paraphrase-multilingual"_s, i18n("Sentence-transformers model that can be used for tasks like clustering or semantic search.")},
        {u"opencoder"_s,
         i18n("OpenCoder is an open and reproducible code LLM family which includes 1.5B and 8B models, supporting chat in English and Chinese languages.")},
        {u"tulu3"_s,
         i18n("Tülu 3 is a leading instruction following model family, offering fully open-source data, code, and recipes by the The Allen Institute for AI.")},
        {u"snowflake-arctic-embed2"_s,
         i18n("Snowflake's frontier embedding model. Arctic Embed 2.0 adds multilingual support without sacrificing English performance or scalability.")},
        {u"granite3-guardian"_s, i18n("The IBM Granite Guardian 3.0 2B and 8B models are designed to detect risks in prompts and/or responses.")},
        {u"exaone3.5"_s,
         i18n("EXAONE 3.5 is a collection of instruction-tuned bilingual (English and Korean) generative models ranging from 2.4B to 32B parameters, developed "
              "and released by LG AI Research.")},
        {u"sailor2"_s, i18n("Sailor2 are multilingual language models made for South-East Asia. Available in 1B, 8B, and 20B parameter sizes.")},
        {u"falcon3"_s,
         i18n("A family of efficient AI models under 10B parameters performant in science, math, and coding through innovative training techniques.")},
        {u"granite3.1-dense"_s,
         i18n("The IBM Granite 2B and 8B models are text-only dense LLMs trained on over 12 trillion tokens of data, demonstrated significant improvements "
              "over their predecessors in performance and speed in IBM’s initial testing.")},
        {u"granite3.1-moe"_s,
         i18n("The IBM Granite 1B and 3B models are long-context mixture of experts (MoE) Granite models from IBM designed for low latency usage.")},
        {u"granite-embedding"_s,
         i18n("The IBM Granite Embedding 30M and 278M models models are text-only dense biencoder embedding models, with 30M available in English only and "
              "278M serving multilingual use cases.")},
        {u"phi4"_s, i18n("Phi-4 is a 14B parameter, state-of-the-art open model from Microsoft.")},
        {u"smallthinker"_s, i18n("A new small reasoning model fine-tuned from the Qwen 2.5 3B Instruct model.")},
        {u"dolphin3"_s,
         i18n("Dolphin 3.0 Llama 3.1 8B 🐬 is the next generation of the Dolphin series of instruct-tuned models designed to be the ultimate general purpose "
              "local model, enabling coding, math, agentic, function calling, and general use cases.")},
        {u"deepseek-r1"_s,
         i18n("DeepSeek's first-generation of reasoning models with comparable performance to OpenAI-o1, including six dense models distilled from DeepSeek-R1 "
              "based on Llama and Qwen.")},
        {u"deepseek-v3"_s, i18n("A strong Mixture-of-Experts (MoE) language model with 671B total parameters with 37B activated for each token.")},
        {u"olmo2"_s,
         i18n("OLMo 2 is a new family of 7B and 13B models trained on up to 5T tokens. These models are on par with or better than equivalently sized fully "
              "open models, and competitive with open-weight models such as Llama 3.1 on English academic benchmarks.")},
        {u"command-r7b"_s,
         i18n("The smallest model in Cohere's R series delivers top-tier speed, efficiency, and quality to build powerful AI applications on commodity GPUs "
              "and edge devices.")},
        {u"openthinker"_s, i18n("A fully open-source family of reasoning models built using a dataset derived by distilling DeepSeek-R1.")},
        {u"deepscaler"_s,
         i18n("A fine-tuned version of Deepseek-R1-Distilled-Qwen-1.5B that surpasses the performance of OpenAI’s o1-preview with just 1.5B parameters on "
              "popular math evaluations.")},
        {u"r1-1776"_s,
         i18n("A version of the DeepSeek-R1 model that has been post trained to provide unbiased, accurate, and factual information by Perplexity.")},
        {u"gemma3"_s, i18n("The current, most capable model that runs on a single GPU.")},
        {u"phi4-mini"_s,
         i18n("Phi-4-mini brings significant enhancements in multilingual support, reasoning, and mathematics, and now, the long-awaited function calling "
              "feature is finally supported.")},
        {u"granite3.2-vision"_s,
         i18n("A compact and efficient vision-language model, specifically designed for visual document understanding, enabling automated content extraction "
              "from tables, charts, infographics, plots, diagrams, and more.")},
        {u"granite3.2"_s, i18n("Granite-3.2 is a family of long-context AI models from IBM Granite fine-tuned for thinking capabilities.")},
        {u"command-r7b-arabic"_s,
         i18n("A new state-of-the-art version of the lightweight Command R7B model that excels in advanced Arabic language capabilities for enterprises in the "
              "Middle East and Northern Africa.")},
        {u"command-a"_s, i18n("111 billion parameter model optimized for demanding enterprises that require fast, secure, and high-quality AI")},
        {u"exaone-deep"_s,
         i18n("EXAONE Deep exhibits superior capabilities in various reasoning tasks including math and coding benchmarks, ranging from 2.4B to 32B parameters "
              "developed and released by LG AI Research.")},
        {u"mistral-small3.1"_s,
         i18n("Building upon Mistral Small 3, Mistral Small 3.1 (2503) adds state-of-the-art vision understanding and enhances long context capabilities up to "
              "128k tokens without compromising text performance.")},
        {u"cogito"_s,
         i18n("Cogito v1 Preview is a family of hybrid reasoning models by Deep Cogito that outperform the best available open models of the same size, "
              "including counterparts from LLaMA, DeepSeek, and Qwen across most standard benchmarks.")},
        {u"deepcoder"_s, i18n("DeepCoder is a fully open-Source 14B coder model at O3-mini level, with a 1.5B version also available.")},
        {u"qwen3"_s,
         i18n("Qwen3 is the latest generation of large language models in Qwen series, offering a comprehensive suite of dense and mixture-of-experts (MoE) "
              "models.")},
        {u"llama4"_s, i18n("Meta's latest collection of multimodal models.")},
        {u"granite3.3"_s,
         i18n("IBM Granite 2B and 8B models are 128K context length language models that have been fine-tuned for improved reasoning and instruction-following "
              "capabilities.")},
        {u"phi4-reasoning"_s,
         i18n("Phi 4 reasoning and reasoning plus are 14-billion parameter open-weight reasoning models that rival much larger models on complex reasoning "
              "tasks.")},
        {u"phi4-mini-reasoning"_s, i18n("Phi 4 mini reasoning is a lightweight open model that balances efficiency with advanced reasoning ability.")},
        {u"gemma3n"_s, i18n("Gemma 3n models are designed for efficient execution on everyday devices such as laptops, tablets or phones.")},
        {u"magistral"_s, i18n("Magistral is a small, efficient reasoning model with 24B parameters.")},
        {u"mistral-small3.2"_s, i18n("An update to Mistral Small that improves on function calling, instruction following, and less repetition errors.")},
        {u"qwen2.5vl"_s, i18n("Flagship vision-language model of Qwen and also a significant leap from the previous Qwen2-VL.")},
        {u"devstral"_s, i18n("Devstral: the best open source model for coding agents.")},
    };
    const QString translatedString = listTranslation.value(modelName);
    if (translatedString.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Missing translation for " << modelName;
    }
    return translatedString;
}
