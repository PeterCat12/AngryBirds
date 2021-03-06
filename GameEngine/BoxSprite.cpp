
#include "AzulCore.h"

#include "EnumName.h"
#include "TextMan.h"
#include "Text.h"
#include "Rect.h"
#include "Image.h"
#include "ImageMan.h"
#include "BoxModel.h"
#include "BoxSprite.h"

//externs must be exterminated

extern GLShaderManager	shaderManager;

BoxSprite :: BoxSprite(  SpriteBatchName::Name spriteBatchName, SpriteName::Name _spriteName, float _lineWidth, const Vect &_color, GameSprite *gSprite)
{
	this->privBoxSprite( spriteBatchName,  _spriteName, _lineWidth, _color, Rect(gSprite->posX, gSprite->posY, gSprite->origWidth, gSprite->origHeight), gSprite->angle);
}




void BoxSprite :: privBoxSprite(  SpriteBatchName::Name spriteBatchName, SpriteName::Name _spriteName, float _lineWidth, const Vect &_color, Rect destRect, float angle)
{
	this->setName( 0 );

	this->lineWidth = _lineWidth;
	this->color = _color;

	this->spriteName = _spriteName;

	BoxModel *p = new BoxModel( destRect );
	this->boxModel = p;

	this->angle = angle;

	this->origWidth = p->destRect.width;
	this->origHeight = p->destRect.height;

	this->posX = p->destRect.x;
	this->posY = p->destRect.y;

	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);

	SBNode *batch = SpriteBatchManager::Find(spriteBatchName);
	batch->addSprite( _spriteName, this);
}

BoxSprite :: BoxSprite(  SpriteBatchName::Name spriteBatchName, SpriteName::Name _spriteName, float _lineWidth, const Vect &_color, Rect destRect)
{
	this->setName( 0 );
	this->spriteBatchName = spriteBatchName;
	this->lineWidth = _lineWidth;
	this->color = _color;

	this->spriteName = _spriteName;

	BoxModel *p = new BoxModel( destRect );
	this->boxModel = p;

	this->angle = 0.0f;

	this->origWidth = p->destRect.width;
	this->origHeight = p->destRect.height;

	this->posX = p->destRect.x;
	this->posY = p->destRect.y;

	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);

	SBNode *batch = SpriteBatchManager::Find(spriteBatchName);
	batch->addSprite( _spriteName, this);
}

// Constructor make sure everything is initialized
BoxSprite :: BoxSprite( const char * const _Name, BoxModel * const p)
{
	this->boxModel = p;
	this->setName( _Name );

	this->angle = 0.0f;

	this->origWidth = p->destRect.width;
	this->origHeight = p->destRect.height;

	this->posX = p->destRect.x;
	this->posY = p->destRect.y;

	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);
};


void BoxSprite::transform( void )
{

	// create the tranformation matrices
	Matrix Scale(SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix RotZ( ROT_Z, angle );
	Matrix Trans( TRANS, this->posX, this->posY, 0.0f);

	// create the origin in the lower left corner
	Matrix TransToOriginLowerLeft( TRANS, -400.f, -300.f, 0.0f);

	// Create the local to world matrix (ie Model)
	this->LocalToWorld =  Scale * RotZ * Trans * TransToOriginLowerLeft;
	                                    
	// Create the ModelView ( LocalToWorld * View)
	// Some pipelines have the project concatenated, others don't
	// Best to keep the separated, you can always join them with a quick multiply
   this->ModelView = this->LocalToWorld * Camera::getViewMatrix();

};


void BoxSprite::setRenderState( void )
{
	// Blends for sprites
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

	// Use the stock shader
	Matrix mvp = ModelView * Camera::getProjMatrix();

	// flat shader
	shaderManager.UseStockShader(GLT_SHADER_FLAT, 
						& mvp, 
						& this->color);

};

void BoxSprite::draw( void )
{  
	if(display)
	{
		glBindVertexArray(this->boxModel->vao);

		/*  render primitives from array data */
		glLineWidth(this->lineWidth);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}
};

void BoxSprite::privDraw()
{
	transform();
	setRenderState();
	draw();
}