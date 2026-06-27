#pragma once
#include "epch.h"

namespace Engine
{
	struct VertexBUfferElements
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		template<typename type>
		static unsigned int GetSizeOfType(typename type)
		{
			switch (type)
			{
			case float: return 4;
			case unsigned int: return 4;
			case unsigned char: return 1;
			}
		}
	};
	class VertexBufferLayout
	{
	private:
		std::vector<VertexBUfferElements> elements;
		unsigned int stride;
	public:
		VertexBufferLayout()
		{ }
		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		template<typename T>
		void Push<float>(unsigned int count)
		{
			VertexBUfferElements vbe;
			vbe.count = count;
			vbe.type = T;
			vbe.normalized = false;
			elements.push_back(vbe);
			stride += count * VertexBUfferElements::GetSizeOfType<float>(float());
		}
		template<typename T>
		void Push<unsigned int>(unsigned int count)
		{
			VertexBUfferElements vbe;
			vbe.count = count;
			vbe.type = T;
			vbe.normalized = false;
			elements.push_back(vbe);
			stride += count * VertexBUfferElements::GetSizeOfType<unsigned int>(unsigned int());
		}
		template<typename T>
		void Push<char>(unsigned int count)
		{
			VertexBUfferElements vbe;
			vbe.count = count;
			vbe.type = T;
			vbe.normalized = true;
			elements.push_back(vbe);
			stride += count * VertexBUfferElements::GetSizeOfType<char>(char());
		}

		inline const std::vector<VertexBUfferElements> GetElements() const { return elements; }
		inline unsigned int GetStride() const { return stride; }
	};
}