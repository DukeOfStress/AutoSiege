# Design Document

## Game Flow
```
START
Hero Selection Phase
LOOP
|
| Recruit Phase
| Combat Phase
|
END
```

## [OG Hero Pool?](https://www.vg247.com/2019/11/11/hearthstone-battlegrounds-heroes-best-tier-list/)

## [Minion Pool](https://www.hearthstonetopdecks.com/guides/hearthstone-battlegrounds-minions-guide/) [or this??](https://www.pcgamesn.com/hearthstone/battlegrounds-cards-list)
```
Tier 1 : 18 copies x 12 cards (IDs:    0 -  511)
Tier 2 : 15 copies x 17 cards (IDs:  512 - 1023)
Tier 3 : 13 copies x 17 cards (IDs: 1024 - 1535)
Tier 4 : 11 copies x 14 cards (IDs: 1536 - 2047)
Tier 5 :  9 copies x 15 cards (IDs: 2048 - 2559)
Tier 6 :  6 copies x  8 cards (IDs: 2560 - 3071)
```
To calculate the card tier from the ID, use:  
`Tier = ID / 512`

## Shop
### Available Actions
```
Reroll  - Costs 1
Freeze  - Costs 0
Buy     - Costs 3
Upgrade - See Tavern Tier	Base Cost 
```

Tavern Tier	Base Cost 
```
2		5 
3		7 
4		8 
5		9 
6		10
```

The number of minions offered to the player starts in 3 and is increases by 1 at tiers 2, 4 and 6

## Timer 

The first round is 60 seconds (time starting at hero choice lasts for 15 seconds, then 12-13 seconds of intro animation before giving control over to the player), and it increases each round by 15 seconds, capping off at 120 seconds.
