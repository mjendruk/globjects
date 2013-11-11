
#include <cassert>

#include <unordered_map>

#include <GLFW/glfw3.h>

#include <glow/logging.h>
#include <glowwindow/events.h>


namespace glow
{

WindowEvent::WindowEvent(Type type)
: m_type(type)
, m_accepted(false)
, m_window(nullptr)
{
}

WindowEvent::~WindowEvent()
{
}

WindowEvent::Type WindowEvent::type() const
{
    return m_type;
}

bool WindowEvent::isAccepted() const
{
    return m_accepted;
}

bool WindowEvent::isIgnored() const
{
    return !m_accepted;
}

void WindowEvent::setAccepted(const bool accepted)
{
    m_accepted = accepted;
}

void WindowEvent::accept()
{
    m_accepted = true;
}

void WindowEvent::ignore()
{
    m_accepted = false;
}

Window* WindowEvent::window() const
{
    return m_window;
}

void WindowEvent::setWindow(Window* window)
{
    m_window = window;
}

KeyEvent::KeyEvent(unsigned int character)
: WindowEvent(KeyTyped)
, m_key(0)
, m_scanCode(0)
, m_action(0)
, m_modifiers(0)
, m_character(character)
{
}

KeyEvent::KeyEvent(int key, int scanCode, int action, int modifiers)
: WindowEvent(action == GLFW_RELEASE ? KeyRelease : KeyPress)
, m_key(key)
, m_scanCode(scanCode)
, m_action(action)
, m_modifiers(modifiers)
, m_character(0)
{
}

int KeyEvent::key() const
{
    return m_key;
}

int KeyEvent::scanCode() const
{
    return m_scanCode;
}

int KeyEvent::action() const
{
    return m_action;
}

int KeyEvent::modifiers() const
{
    return m_modifiers;
}

unsigned int KeyEvent::character() const
{
    return m_character;
}


ResizeEvent::ResizeEvent(int width, int height, bool framebuffer)
: WindowEvent(framebuffer ? FrameBufferResize : Resize)
, m_size(width, height)
{
}

const glm::ivec2 & ResizeEvent::size() const
{
    return m_size;
}

int ResizeEvent::width() const
{
    return m_size.x;
}

int ResizeEvent::height() const
{
    return m_size.y;
}


MouseEvent::MouseEvent(const int x, const int y)
: WindowEvent(MouseMove)
, m_button(-1)
, m_action(-1)
, m_modifiers(0)
, m_pos(x, y)
{
}

MouseEvent::MouseEvent(const int x, const int y, const int button, const int action, const int modifiers)
: WindowEvent(action == GLFW_RELEASE ? MouseRelease : MousePress)
, m_button(button)
, m_action(action)
, m_modifiers(modifiers)
, m_pos(x, y)
{
}

int MouseEvent::button() const
{
    return m_button;
}

int MouseEvent::action() const
{
    return m_action;
}

int MouseEvent::modifiers() const
{
    return m_modifiers;
}

int MouseEvent::x() const
{
    return m_pos.x;
}

int MouseEvent::y() const
{
    return m_pos.y;
}

const glm::ivec2 & MouseEvent::pos() const
{
    return m_pos;
}

ScrollEvent::ScrollEvent(
    const double xOffset
,   const double yOffset
,   const int x
,   const int y)
: WindowEvent(Scroll)
, m_offset(xOffset, yOffset)
, m_pos(x, y)
{
}

const glm::vec2 & ScrollEvent::offset() const
{
    return m_offset;
}

const glm::ivec2 & ScrollEvent::pos() const
{
    return m_pos;
}


MoveEvent::MoveEvent(int x, int y)
: WindowEvent(Move)
, m_pos(x, y)
{
}

int MoveEvent::x() const
{
    return m_pos.x;
}

int MoveEvent::y() const
{
    return m_pos.y;
}

const glm::ivec2 & MoveEvent::pos() const
{
    return m_pos;
}

PaintEvent::PaintEvent()
: WindowEvent(Paint)
{
}

CloseEvent::CloseEvent()
: WindowEvent(Close)
{
}

IdleEvent::IdleEvent()
: WindowEvent(Idle)
{
}

FocusEvent::FocusEvent(bool hasFocus)
: WindowEvent(Focus)
, m_hasFocus(hasFocus)
{
}

bool FocusEvent::hasFocus() const
{
    return m_hasFocus;
}

IconifyEvent::IconifyEvent(bool isIconified)
: WindowEvent(Iconify)
, m_isIconified(isIconified)
{
}

bool IconifyEvent::isIconified() const
{
    return m_isIconified;
}


} // namespace glow
