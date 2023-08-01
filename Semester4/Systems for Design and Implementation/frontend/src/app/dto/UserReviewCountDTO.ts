import { UserProfile } from "../model/UserProfile"

export default interface UserReviewCountDTO {
    userProfileDTO: UserProfile,
    count: number
}