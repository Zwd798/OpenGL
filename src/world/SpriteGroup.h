#pragma once
#include "pch.h"
#include "Tile.h"

namespace engine
{
	class Renderer;

	class SpriteGroup
	{
	public:
		SpriteGroup(const std::unordered_map<Sprite*, std::vector<Tile>>& data);
		SpriteGroup(const SpriteGroup& group) = delete;
		//SpriteGroup(SpriteGroup&& group) = delete; // If we delete the copy constructor and move constructor, the program will not compile because in the spritegroup cpp file we are using emplace_back function which may use both theese methods
		SpriteGroup(SpriteGroup&& group) noexcept :
			m_RenderObject(group.m_RenderObject),
			m_Sprites(std::move(group.m_Sprites))
		{
			group.m_RenderObject = nullptr;
		}
		~SpriteGroup()
		{
			delete m_RenderObject;
		}


		void Draw(Renderer& renderer) const;
		static uint GetMaxSpriteCount()
		{
			return gfx::getMaxTextureUnits();
		}
	private:
		// everything in this group will use a single VAO and IBO
		gfx::RenderObject* m_RenderObject;
		// list of Sprites to send to our Renderer
		std::vector<Sprite*> m_Sprites;
	};
}