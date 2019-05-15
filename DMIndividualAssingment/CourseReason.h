#pragma once

//TODO
enum CourseReason {
	SubjectInterest = 1 << 0,
	MandatoryCourse = 1 << 1,
	Job = 1 << 4,
	OtherOptionals = 1 << 5,
	NotTaking = 1 << 6,
	Other = 1 << 7					// HomePlanet, WhyShouldI
};