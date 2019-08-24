#pragma once
#include "GameObject.h"
#include "Utilities.h"

/**
 * A general custom interface for Sprite objects. It provides wrapper features for native Sprite object,
 * like handling properly the texture loading for the Sprite from a file path.
 * Keep this interface not dependent on specific projects properties, so that it can be reused among different projects.
 */
class SpriteWrapper : 
	public virtual sf::Sprite
{
	public:
		/**
		 * Constructor loading the specified texture given the file name.
		 * An assert statement makes sure the default image is loaded.
		 */
		SpriteWrapper(const std::string& fileName);

		virtual ~SpriteWrapper() { LOG(__func__) }

		/**
		 * Allows to set explicitly the sizes in pixels for the object (shape or sprite).
		 * The SFML API lacks of a setSize method, it only exposes a way to rescale objects.
		 * The current method retrieves the sizes of the original object, hence calculating and applying
		 * the scaling factor required to have an object surrounding rectangle with the input x and y sizes.
		 *
		 * IMPORTANT: this method assumes that the visible object has non-zero sizes when invoking this method.
		 * This can be enforced in the derived classes invariants.
		 */
		virtual void SetSize(float sizeX, float sizeY);

		/**
		 * If failure when loading the texture an exception is thrown.
		 * The default texture must be specified in the constructor.
		 * This method can be invoked when the default image should be changed.
		 */
		virtual void LoadTexture(std::string filename);

		virtual bool IsTextureLoaded() const { return _isLoaded; }

	protected:
		sf::Texture _image;
		bool _isLoaded = false;
		std::string _filename;
};
