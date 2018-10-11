#define EVENTS_ARRAY_SIZE 24
void (*events[EVENTS_ARRAY_SIZE])() = {};

//functions for common events:

void Closed()
{
	window.close();
}

void nothing()
{}

void setCommonEvents() //for all the scenes
{
	events[0] = Closed;
	events[1] = nothing; //resized
	events[2] = nothing; //lost focus
	events[3] = nothing; //gained focus
	events[7] = nothing; //mouse wheel moved
	events[12] = nothing; //mouse entered
	events[13] = nothing; //mouse left
	events[14] = nothing;
	events[15] = nothing;
	events[16] = nothing;
	events[17] = nothing;
	events[18] = nothing;
	events[19] = nothing;
	events[20] = nothing;
	events[21] = nothing;
	events[22] = nothing;
	events[23] = nothing;
}
