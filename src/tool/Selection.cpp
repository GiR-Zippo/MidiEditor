#include "Selection.h"
#include "../gui/EventWidget.h"

Selection* Selection::_selectionInstance = new Selection(0);
EventWidget* Selection::_eventWidget = 0;

Selection::Selection(MidiFile* file)
{
    _file = file;
    if (_eventWidget) {
        _eventWidget->setEvents(_selectedEvents);
        _eventWidget->reload();
    }
}

Selection::Selection(Selection& other)
{
    _file = other._file;
    _selectedEvents = other._selectedEvents;
}

ProtocolEntry* Selection::copy()
{
    return new Selection(*this);
}

void Selection::reloadState(ProtocolEntry* entry)
{
    Selection* other = dynamic_cast<Selection*>(entry);
    if (!other) {
        return;
    }
    _selectedEvents = other->_selectedEvents;
    if (_eventWidget) {
        _eventWidget->setEvents(_selectedEvents);
        //_eventWidget->reload();
    }
}

MidiFile* Selection::file()
{
    return _file;
}

Selection* Selection::instance()
{
    return _selectionInstance;
}

void Selection::setFile(MidiFile* file)
{
    // Delete the old selection instance to prevent memory leak
    if (_selectionInstance) {
        delete _selectionInstance;
    }

    // create new selection
    _selectionInstance = new Selection(file);
}

QList<MidiEvent*>& Selection::selectedEvents()
{
    return _selectedEvents;
}

void Selection::setSelection(QList<MidiEvent*> selections)
{
    protocol(copy(), this);
    _selectedEvents = selections;
    if (_eventWidget) {
        _eventWidget->setEvents(_selectedEvents);
        //_eventWidget->reload();
    }
}

void Selection::clearSelection()
{
    setSelection(QList<MidiEvent*>());
    if (_eventWidget) {
        _eventWidget->setEvents(_selectedEvents);
        //_eventWidget->reload();
    }
}
