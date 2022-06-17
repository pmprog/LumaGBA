
#pragma once

typedef unsigned char                   u8;
typedef volatile unsigned char          vu8;
typedef unsigned short                  u16;
typedef volatile unsigned short         vu16;
typedef unsigned int                    u32;
typedef volatile unsigned int           vu32;
typedef signed char                     s8;
typedef volatile signed char            vs8;
typedef signed short                    s16;
typedef volatile signed short           vs16;
typedef signed int                      s32;
typedef volatile signed int             vs32;

typedef void(*NetworkConnectionCallback)(u8 ClientID, u8 Connected);
typedef void(*NetworkDataCallback)(u16 ServerData, u16 Player1Data, u16 Player2Data, u16 Player3Data);

typedef enum ControllerInput
{
    INPUT_NONE    = 0x0000,
    BUTTON_A      = 0x0001,
    BUTTON_B      = 0x0002,
    BUTTON_Select = 0x0004,
    BUTTON_Start  = 0x0008,
    DPAD_Right    = 0x0010,
    DPAD_Left     = 0x0020,
    DPAD_Up       = 0x0040,
    DPAD_Down     = 0x0080,
    BUTTON_R      = 0x0100,
    BUTTON_L      = 0x0200,
    BUTTON_SUPER  = 0x0400, // Not available on GBA
    BUTTON_QUIT   = 0x0800, // Not available on GBA
} ControllerInput;

typedef enum ColourDepth
{
    COLOURS_NONE  = 0x0000,
    COLOURS_4BPP  = 0x0001,
    COLOURS_8BPP  = 0x0002,
} ColourDepth;

typedef enum Mirroring
{
    MIRROR_NONE       = 0x0000,
    MIRROR_HORIZONTAL = 0x0001,
    MIRROR_VERTICAL   = 0x0002,
    MIRROR_BOTH       = 0x0003,
} Mirroring;

typedef enum SpriteSize
{
    SIZE_8x8          = 0x0000,
    SIZE_16x16        = 0x0001,
    SIZE_32x32        = 0x0002,
    SIZE_64x64        = 0x0003,
} SpriteSize;

typedef enum TileSize
{
    SIZE_8        = 0x0000,
    SIZE_16       = 0x0001,
    SIZE_32       = 0x0002,
    SIZE_64       = 0x0003,
} TileSize;

typedef enum Palette
{
    PALETTE_C64,
    PALETTE_ARNE16,
    PALETTE_ARNE32,
} Palette;

typedef struct Colour
{
    u8 R;
    u8 G;
    u8 B;
} Colour;

typedef void(*StageCallback)();
typedef void(*EventCallback)(void* Argument);

typedef enum EventFlags
{
    FLAGS_EXECUTE_EACH_FRAME = 0x01,    // This flag causes the callback to be called every frame instead of at the end
} EventFlags;

typedef struct EventRecord
{
    u8 FrameDelay;                      // How many frames to wait before activating.
    EventCallback Callback;             // Callback method
    void* Argument;                     // Any data you want to pass to the callback
    EventFlags Flags;                   // Additional flags for altering behaviour
} EventRecord;

typedef struct StageRecord
{
    StageCallback Start;                // Called when the engine is changing to this stage
    StageCallback Update;               // Called every frame whilst the stage is active
    StageCallback Finish;               // Called when then engine is changing to a new stage
} StageRecord;

